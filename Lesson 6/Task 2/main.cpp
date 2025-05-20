#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>


namespace dbo = Wt::Dbo;


class Shop;
class Book;
class Stock;
class Sale;

class Publisher {
public:
	Publisher() {}
	explicit Publisher(std::string name) : name(name) {}

	std::string name{};
	dbo::collection<dbo::ptr<Book>> books{};

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, name, "name");
		dbo::hasMany(a, books, dbo::ManyToOne, "publisher");
	}
};

class Shop {
public:
	Shop() {}
	explicit Shop(std::string name) : name(name) {}

	std::string name{};
	dbo::collection<dbo::ptr<Stock>> stocks{};

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, name, "name");
		dbo::hasMany(a, stocks, dbo::ManyToOne, "shop");
	}
};

class Book {
public:
	Book() {}
	explicit Book(std::string title) : title(title) {}

	std::string title{};
	dbo::ptr<Publisher> publisher{};
	dbo::collection<dbo::ptr<Stock>> stocks{};

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, title, "title");
		dbo::belongsTo(a, publisher, "publisher");
		dbo::hasMany(a, stocks, dbo::ManyToOne, "book");
	}
};

class Stock {
public:
	Stock() {}
	explicit Stock(int count) : count(count) {}

	int count{};
	dbo::ptr<Book> book{};
	dbo::ptr<Shop> shop{};
	dbo::collection<dbo::ptr<Sale>> sales{};

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, count, "count");
		dbo::belongsTo(a, book, "book");
		dbo::belongsTo(a, shop, "shop");
		dbo::hasMany(a, sales, dbo::ManyToOne, "stock");
	}
};

class Sale {
public:
	Sale() {}
	explicit Sale(int price, std::string date_sale, int count) :
		price(price), date_sale(date_sale), count(count) {}

	int price{};
	std::string date_sale{};
	int count{};
	dbo::ptr<Stock> stock{};

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, price, "price");
		dbo::field(a, date_sale, "date_sale");
		dbo::field(a, count, "count");
		dbo::belongsTo(a, stock, "stock");
	}
};


template <typename T>
void addEntry(dbo::Session& session, T* pObj)
{
	dbo::Transaction transaction{ session };

	std::unique_ptr<T> upObj{ pObj };
	dbo::ptr<T> ptr = session.add(std::move(upObj));

	transaction.commit();
}

template <typename T, typename T2>
void addEntry(dbo::Session& session, T* pObj, std::string str)
{
}

template <typename T, typename T2>
void addEntry(dbo::Session& session, T* pObj, int id)
{
}

template <typename T, typename T2, typename T3>
void addEntry(dbo::Session& session, T* pObj, std::string str1, std::string str2)
{
}

template <>
void addEntry<Book, Publisher>(dbo::Session& session, Book* pObj, std::string str)
{
	dbo::Transaction transaction{ session };

	std::unique_ptr<Book> upObj{ pObj };
	dbo::ptr<Book> ptr = session.add(std::move(upObj));

	dbo::ptr<Publisher> publisher = session.find<Publisher>().where("name = ?").bind(str);
	ptr.modify()->publisher = publisher;

	transaction.commit();
}

template <>
void addEntry<Stock, Book, Shop>(dbo::Session& session, Stock* pObj,
	std::string str1, std::string str2)
{
	dbo::Transaction transaction{ session };

	std::unique_ptr<Stock> upObj{ pObj };
	dbo::ptr<Stock> ptr = session.add(std::move(upObj));

	dbo::ptr<Book> book = session.find<Book>().where("title = ?").bind(str1);
	dbo::ptr<Shop> shop = session.find<Shop>().where("name = ?").bind(str2);
	ptr.modify()->book = book;
	ptr.modify()->shop = shop;

	transaction.commit();
}

template <>
void addEntry<Sale, Stock>(dbo::Session& session, Sale* pObj, int id)
{
	dbo::Transaction transaction{ session };

	std::unique_ptr<Sale> upObj{ pObj };
	dbo::ptr<Sale> ptr = session.add(std::move(upObj));

	dbo::ptr<Stock> stock = session.find<Stock>().where("id = ?").bind(id);
	ptr.modify()->stock = stock;

	transaction.commit();
}

template <typename T>
std::set<std::string> getShops(dbo::Session& session, std::string str)
{
}

template <>
std::set<std::string> getShops<Publisher>(dbo::Session& session, std::string str)
{
	std::set<std::string> ret{};

	dbo::Transaction transaction{ session };

	dbo::ptr<Publisher> publisher = session.find<Publisher>().where("name = ?").bind(str);

	dbo::collection<dbo::ptr<Book>> books = publisher->books;
	
	for (const auto& book : books)
	{
		dbo::collection<dbo::ptr<Stock>> stocks = book->stocks;

		for (const auto& stock : stocks)
		{
			ret.emplace(stock->shop->name);
		}
	}

	transaction.commit();
	return ret;
}



int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	try
	{
		std::string connectionString =
			"host=localhost "
			"port=5432 "
			"dbname=test "
			"user=postgres "
			"password=Veryspecial1335!";
		auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);
		dbo::Session session;
		session.setConnection(std::move(postgres));

		session.mapClass<Publisher>("publisher");
		session.mapClass<Shop>("shop");
		session.mapClass<Book>("book");
		session.mapClass<Stock>("stock");
		session.mapClass<Sale>("sale");

		session.dropTables();
		session.createTables();

		addEntry<Publisher>(session, new Publisher{ "Lee" });
		addEntry<Publisher>(session, new Publisher{ "Orwell" });
		addEntry<Publisher>(session, new Publisher{ "Fitzgerald" });
		addEntry<Publisher>(session, new Publisher{ "Salinger" });
		addEntry<Publisher>(session, new Publisher{ "Auste" });

		addEntry<Book, Publisher>(session, new Book{ "1984" }, "Orwell");
		addEntry<Book, Publisher>(session, new Book{ "To Kill a Mockingbird" }, "Lee");
		addEntry<Book, Publisher>(session, new Book{ "Animal Farm" }, "Orwell");
		addEntry<Book, Publisher>(session, new Book{ "The Great Gatsby" }, "Fitzgerald");
		addEntry<Book, Publisher>(session, new Book{ "The Catcher in the Rye" }, "Salinger");
		addEntry<Book, Publisher>(session, new Book{ "Pride and Prejudice" }, "Auste");

		addEntry<Shop>(session, new Shop{ "Altufevo" });
		addEntry<Shop>(session, new Shop{ "Brateevo" });
		addEntry<Shop>(session, new Shop{ "Chertanovo" });
		addEntry<Shop>(session, new Shop{ "Khimki" });

		addEntry<Stock, Book, Shop>(session, new Stock{ 11 }, "1984", "Altufevo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 22 }, "To Kill a Mockingbird", "Altufevo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 33 }, "To Kill a Mockingbird", "Chertanovo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 44 }, "To Kill a Mockingbird", "Brateevo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 55 }, "Animal Farm", "Khimki");
		addEntry<Stock, Book, Shop>(session, new Stock{ 66 }, "Animal Farm", "Chertanovo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 77 }, "The Great Gatsby", "Altufevo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 88 }, "The Great Gatsby", "Chertanovo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 99 }, "The Catcher in the Rye", "Altufevo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 111 }, "The Catcher in the Rye", "Khimki");
		addEntry<Stock, Book, Shop>(session, new Stock{ 122 }, "The Catcher in the Rye", "Brateevo");
		addEntry<Stock, Book, Shop>(session, new Stock{ 133 }, "Pride and Prejudice", "Brateevo");

		addEntry<Sale, Stock>(session, new Sale{ 35, "01.01.2025", 1 }, 0);
		addEntry<Sale, Stock>(session, new Sale{ 47, "01.01.2025", 2 }, 3);
		addEntry<Sale, Stock>(session, new Sale{ 10, "01.01.2025", 1 }, 5);
		addEntry<Sale, Stock>(session, new Sale{ 21, "01.01.2025", 2 }, 7);
		addEntry<Sale, Stock>(session, new Sale{ 27, "01.01.2025", 1 }, 8);
		addEntry<Sale, Stock>(session, new Sale{ 54, "01.01.2025", 3 }, 9);

		std::string publisher_name{};
		std::cout << "Enter publisher name: ";
		std::cin >> publisher_name;

		auto shops = getShops<Publisher>(session, publisher_name);

		int idx{};
		std::cout << std::endl << "Shop list:" << std::endl;
		for (const auto& shop : shops)
		{
			std::cout << idx << ": " << shop << std::endl;
			idx++;
		}		
	}
	catch (const dbo::Exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}