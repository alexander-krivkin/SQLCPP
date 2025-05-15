#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <pqxx/pqxx>


namespace ak
{
	struct Client final
	{
		std::string firstName{};
		std::string lastName{};
		std::string email{};
		std::vector<std::string> phones{};
	};


	class ClientDB final
	{
	public:
		ClientDB();
		explicit ClientDB(const ClientDB& obj) = delete;
		ClientDB& operator=(const ClientDB& obj) = delete;
		~ClientDB() {}

		void deleteTables();
		void createTables();
		void print();
		void addClient(Client client);
		void deleteClient(std::string firstName, std::string lastName);
		void changeClientEmail(std::string firstName, std::string lastName, std::string email);
		void addClientPhone(std::string firstName, std::string lastName, std::string phone);
		void deleteClientPhone(std::string firstName, std::string lastName, std::string phone);
		std::string getClientEmail(std::string firstName, std::string lastName);
		std::vector<std::string> getClientPhones(std::string firstName, std::string lastName);

	private:
		std::unique_ptr<pqxx::connection> upConnection_;
		std::unique_ptr<pqxx::work> upWork_{};
	};
}

