-- Задание 2
SELECT name, duration
FROM Track
ORDER BY duration DESC
LIMIT 1;

SELECT name
FROM Track
WHERE NOT duration < 3.5;

SELECT name
FROM Collection
WHERE year BETWEEN 2018 AND 2020;

SELECT name
FROM Musician
WHERE name NOT LIKE '% %';

SELECT name
FROM Track
WHERE name LIKE '%my%' OR name LIKE'%My%';


-- Задание 3
SELECT Genre.name, COUNT(*) FROM GenreMusician
LEFT JOIN Genre ON Genre.id = GenreMusician.id_genre
GROUP BY Genre.name
ORDER BY COUNT(id_musician);

SELECT Album.name, COUNT(*) FROM Track
LEFT JOIN Album ON Album.id = Track.id_album
WHERE Album.year BETWEEN 2019 AND 2020
GROUP BY Album.name, Album.year;

SELECT Album.name, AVG(duration) FROM Track
LEFT JOIN Album ON Album.id = Track.id_album
GROUP BY Album.name, Album.year;

SELECT Musician.name FROM AlbumMusician
LEFT JOIN Album ON Album.id = AlbumMusician.id_album
LEFT JOIN Musician ON Musician.id = AlbumMusician.id_musician
WHERE Album.year != 2020
GROUP BY Musician.name;

SELECT Collection.name, Musician.name FROM TrackCollection
LEFT JOIN Track ON Track.id = TrackCollection.id_track
LEFT JOIN Collection ON Collection.id = TrackCollection.id_collection
LEFT JOIN Album ON Album.id = Track.id_album
LEFT JOIN AlbumMusician ON AlbumMusician.id_album = Album.id
LEFT JOIN Musician ON Musician.id = AlbumMusician.id_musician
WHERE Musician.name = 'Roxette'
GROUP BY Collection.name, Musician.name;


-- Задание 4
SELECT Album.name FROM AlbumMusician
LEFT JOIN Album ON Album.id = AlbumMusician.id_album
LEFT JOIN Musician ON Musician.id = AlbumMusician.id_musician
LEFT JOIN GenreMusician ON GenreMusician.id_musician = Musician.id
GROUP BY Album.name
HAVING COUNT(GenreMusician.id_genre) > 1;

SELECT Track.name, Collection.name FROM TrackCollection
FULL JOIN Track ON Track.id = TrackCollection.id_track
FULL JOIN Collection ON Collection.id = TrackCollection.id_collection
GROUP BY Track.name, Collection.name
HAVING COUNT(TrackCollection.id_collection) = 0;

SELECT Musician.name FROM AlbumMusician
LEFT JOIN Album ON Album.id = AlbumMusician.id_album
LEFT JOIN Musician ON Musician.id = AlbumMusician.id_musician
LEFT JOIN Track ON Track.id_album = Album.id
GROUP BY Musician.name
HAVING MIN(Track.duration) = (SELECT MIN(duration) FROM Track);

SELECT Album.name, COUNT(Track.id) FROM Album
LEFT JOIN Track ON Track.id_album = Album.id
GROUP BY Album.name
HAVING COUNT(Track.id) = (
	SELECT COUNT(Track.id) FROM Album
	LEFT JOIN Track ON Track.id_album = Album.id
	GROUP BY Album.name
	ORDER BY COUNT(Track.id) ASC
	LIMIT 1
);