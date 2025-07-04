CREATE TABLE IF NOT EXISTS Genre (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS Album (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	year SMALLINT NOT NULL
);

CREATE TABLE IF NOT EXISTS Musician (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS GenreMusician (
	id SERIAL PRIMARY KEY,
	id_genre INTEGER NOT NULL REFERENCES Genre(id),
	id_musician INTEGER NOT NULL REFERENCES Musician(id)
);

CREATE TABLE IF NOT EXISTS AlbumMusician (
	id SERIAL PRIMARY KEY,
	id_album INTEGER NOT NULL REFERENCES Album(id),
	id_musician INTEGER NOT NULL REFERENCES Musician(id)
);

CREATE TABLE IF NOT EXISTS Track (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	duration REAL NOT NULL,
	id_album INTEGER NOT NULL REFERENCES Album(id)
);

CREATE TABLE IF NOT EXISTS Collection (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	year SMALLINT NOT NULL
);

CREATE TABLE IF NOT EXISTS TrackCollection (
	id SERIAL PRIMARY KEY,
	id_track INTEGER NOT NULL REFERENCES Track(id),
	id_collection INTEGER NOT NULL REFERENCES Collection(id)
);
