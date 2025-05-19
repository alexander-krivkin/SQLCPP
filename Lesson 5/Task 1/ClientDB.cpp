#include "ClientDB.h"


namespace ak
{
	ClientDB::ClientDB()
	{
		std::string str1{ "host=localhost port=5432 dbname=test user=postgres password=Veryspecial1335!" };

		upConnection_ = std::make_unique<pqxx::connection>(str1);
		std::cout << "Connected to DB: " << upConnection_->dbname() << std::endl;
	}

	void ClientDB::deleteTables()
	{
		std::string str1{
			"DROP TABLE IF EXISTS client_phone CASCADE;" };
		std::string str2{
			"DROP TABLE IF EXISTS client CASCADE;" };
		std::string str3{
			"DROP TABLE IF EXISTS phone CASCADE;" };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str1);
		upWork_->exec(str2);
		upWork_->exec(str3);
		upWork_->commit();
		std::cout << "Tables deleted from DB: " << upConnection_->dbname() << std::endl;
	}

	void ClientDB::createTables()
	{
		std::string str1{
			"CREATE TABLE IF NOT EXISTS client( "
			"id SERIAL PRIMARY KEY, "
			"first_name VARCHAR(20) NOT NULL, "
			"last_name VARCHAR(20) NOT NULL, "
			"email VARCHAR(20) UNIQUE NOT NULL "
			"); " };
		std::string str2{
			"CREATE TABLE IF NOT EXISTS phone( "
			"id SERIAL PRIMARY KEY, "
			"number VARCHAR(11) UNIQUE NOT NULL "
			"); " };
		std::string str3{
			"CREATE TABLE IF NOT EXISTS client_phone( "
			"client_id INTEGER NOT NULL REFERENCES client(id), "
			"phone_id INTEGER NOT NULL REFERENCES phone(id), "
			"PRIMARY KEY (client_id, phone_id) "
			"); " };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str1);
		upWork_->exec(str2);
		upWork_->exec(str3);
		upWork_->commit();
		std::cout << "Tables created for DB: " << upConnection_->dbname() << std::endl;
	}

	void ClientDB::print()
	{
		std::cout << std::endl << "Printing DB: " << upConnection_->dbname() << std::endl;
		std::cout << std::setw(20) << "first_name:" << std::setw(20) << "last_name:"
			<< std::setw(20) << "email:" << std::setw(15) << "phones:" << std::endl;

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		for (auto [firstName, lastName, email] : upWork_->query<std::string, std::string, std::string>
			("SELECT first_name, last_name, email FROM client ORDER BY first_name, last_name;"))
		{
			std::cout << std::setw(20) << firstName << std::setw(20) << lastName
				<< std::setw(20) << email << std::setw(15);
				
			upWork_->commit();
			auto phones = getClientPhones(firstName, lastName);
			upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());

			for (auto phone : phones)
			{
				std::cout << phone << std::setw(15);
			}
			std::cout << std::endl;
		}
		upWork_->commit();
	}

	void ClientDB::addClient(Client client)
	{
		std::string str1{
			"INSERT INTO client(first_name, last_name, email) "
			"VALUES($1, $2, $3);" };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str1, pqxx::params{ client.firstName, client.lastName, client.email });
		upWork_->commit();

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		for (auto& phone : client.phones)
		{
			std::string str2{
				"INSERT INTO phone(number) "
				"VALUES($1);" };

			upWork_->exec(str2, pqxx::params{ phone });
		}
		upWork_->commit();

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		for (auto& phone : client.phones)
		{
			std::string str3{
				"INSERT INTO client_phone(client_id, phone_id) "
				"VALUES("
				"(SELECT id FROM client "
				"WHERE first_name = $1 AND last_name = $2), "
				"(SELECT id FROM phone "
				"WHERE number = $3));" };

			upWork_->exec(str3, pqxx::params{ client.firstName, client.lastName, phone });
		}
		upWork_->commit();
	}

	void ClientDB::deleteClient(std::string firstName, std::string lastName)
	{
		auto phones = getClientPhones(firstName, lastName);

		std::string str1{
			"DELETE FROM client_phone "
			"WHERE client_id = "
			"(SELECT id FROM client "
			"WHERE first_name = $1 AND last_name = $2);" };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str1, pqxx::params{ firstName, lastName });
		upWork_->commit();

		std::string str2{
			"DELETE FROM client "
			"WHERE first_name = $1 AND last_name = $2;" };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str2, pqxx::params{ firstName, lastName });
		upWork_->commit();

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		for (auto& phone : phones)
		{
			std::string str3{
				"DELETE FROM phone "
				"WHERE number = $1;" };

			upWork_->exec(str3, pqxx::params{ phone });
		}
		upWork_->commit();
	}

	void ClientDB::changeClientEmail(std::string firstName, std::string lastName, std::string email)
	{
		std::string str1{
			"UPDATE client "
			"SET email = $1 "
			"WHERE first_name = $2 AND last_name = $3;" };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str1, pqxx::params{ email, firstName, lastName });
		upWork_->commit();
	}

	void ClientDB::addClientPhone(std::string firstName, std::string lastName, std::string phone)
	{
		std::string str1{
			"INSERT INTO phone(number) "
			"VALUES($1);" };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str1, pqxx::params{ phone });
		upWork_->commit();

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		std::string str2{
			"INSERT INTO client_phone(client_id, phone_id) "
			"VALUES("
			"(SELECT id FROM client "
			"WHERE first_name = $1 AND last_name = $2), "
			"(SELECT id FROM phone "
			"WHERE number = $3));" };

		upWork_->exec(str2, pqxx::params{ firstName, lastName, phone });
		upWork_->commit();
	}

	void ClientDB::deleteClientPhone(std::string firstName, std::string lastName, std::string phone)
	{
		std::string str1{
		"DELETE FROM client_phone "
		"WHERE client_id = "
		"(SELECT id FROM client "
		"WHERE first_name = $1 AND last_name = $2);" };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str1, pqxx::params{ firstName, lastName });
		upWork_->commit();

		std::string str2{
			"DELETE FROM phone "
			"WHERE number = $1;" };

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		upWork_->exec(str2, pqxx::params{ phone });
		upWork_->commit();
	}

	std::string ClientDB::getClientEmail(std::string firstName, std::string lastName)
	{
		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		for (auto [client_id, email] : upWork_->query<int, std::string>
			("SELECT id, email FROM client "
			"WHERE first_name = '" + firstName + "' AND last_name = '" + lastName +
			"';"))
		{
			upWork_->commit();
			return email;
		}
	}

	std::vector<std::string> ClientDB::getClientPhones(std::string firstName, std::string lastName)
	{
		std::vector<std::string> phones{};

		upWork_ = std::make_unique<pqxx::work>(*upConnection_.get());
		for (auto [client_id, phone] : upWork_->query<int, std::string>
			("SELECT client.id, phone.number FROM client_phone "
			"LEFT JOIN client ON client.id = client_phone.client_id "
			"LEFT JOIN phone ON phone.id = client_phone.phone_id "
			"WHERE client.first_name = '" + firstName + "' AND client.last_name = '" + lastName +
			"';"))
		{
			phones.push_back(phone);
		}

		upWork_->commit();
		return phones;
	}
}