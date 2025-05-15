#include <windows.h>
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#pragma comment(lib, "ws2_32.lib")

#include "ClientDB.h"


int main()
{
	SetConsoleOutputCP(CP_UTF8);

	try
	{
		ak::ClientDB clientDB{};
		clientDB.deleteTables();
		clientDB.createTables();
		clientDB.addClient({ "Ivan", "Ivanov", "ivanov@mail.ru", { "0000000000", "1000000000" } });
		clientDB.addClient({ "Petr", "Petrov", "petrov@mail.ru", {} });
		clientDB.addClient({ "Sidor", "Sidorov", "sidorov@mail.ru", {} });
		clientDB.addClient({ "Afanasy", "Pupkin", "pupkin@mail.ru", { "0001234567" } });
		clientDB.print();

		clientDB.addClient({ "Darja", "Krasotkina", "krasotkina@mail.ru", {} });
		clientDB.deleteClient("Sidor", "Sidorov");
		clientDB.changeClientEmail("Ivan", "Ivanov", "111@mail.ru");
		clientDB.changeClientEmail("Petr", "Petrov", "222@mail.ru");
		clientDB.changeClientEmail("Sidor", "Sidorov", "333@mail.ru");
		clientDB.addClientPhone("Ivan", "Ivanov", "0001111111");
		clientDB.addClientPhone("Ivan", "Ivanov", "0002222222");
		clientDB.addClientPhone("Petr", "Petrov", "0007777777");
		clientDB.deleteClient("Petr", "Petrov");
		clientDB.deleteClientPhone("Afanasy", "Pupkin", "0001234567");
		clientDB.print();

		auto email = clientDB.getClientEmail("Afanasy", "Pupkin");
		auto phones = clientDB.getClientPhones("Ivan", "Ivanov");
    }
	catch (const pqxx::sql_error& ex)
	{
		std::cout << ex.what() << std::endl << std::endl;
		system("pause");
        return EXIT_FAILURE;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	std::cout << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}