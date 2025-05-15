INSERT INTO Genre(name)
VALUES('Doom metal');
INSERT INTO Genre(name)
VALUES('Pop rock');
INSERT INTO Genre(name)
VALUES('Melodic death metal');
INSERT INTO Genre(name)
VALUES('Art rock');

INSERT INTO Album(name, year)
VALUES('Wildhoney', 2018);
INSERT INTO Album(name, year)
VALUES('Joyride', 2020);
INSERT INTO Album(name, year)
VALUES('Hatebreeder', 2020);
INSERT INTO Album(name, year)
VALUES('The Division Bell', 2021);

INSERT INTO Musician(name)
VALUES('Tiamat');
INSERT INTO Musician(name)
VALUES('Roxette');
INSERT INTO Musician(name)
VALUES('Children of Bodom');
INSERT INTO Musician(name)
VALUES('Pink Floyd');

INSERT INTO GenreMusician(id_genre, id_musician)
VALUES(1, 1);
INSERT INTO GenreMusician(id_genre, id_musician)
VALUES(2, 2);
INSERT INTO GenreMusician(id_genre, id_musician)
VALUES(3, 3);
INSERT INTO GenreMusician(id_genre, id_musician)
VALUES(4, 4);
INSERT INTO GenreMusician(id_genre, id_musician)
VALUES(4, 1);

INSERT INTO AlbumMusician(id_album, id_musician)
VALUES(1, 1);
INSERT INTO AlbumMusician(id_album, id_musician)
VALUES(2, 2);
INSERT INTO AlbumMusician(id_album, id_musician)
VALUES(3, 3);
INSERT INTO AlbumMusician(id_album, id_musician)
VALUES(4, 4);


-- Альбом Wildhoney
INSERT INTO Track(name,	duration, id_album)
VALUES('Wildhoney', 0.52, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('Whatever That Hurts', 5.47, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('The Ar', 5.03, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('25th Floor', 1.49, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('Gaia', 6.25, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('Visionaire', 4.19, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('Kaleidoscope', 1.19, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('Do You Dream of Me?', 5.07, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('Planets', 3.11, 1);
INSERT INTO Track(name,	duration, id_album)
VALUES('A Pocket Size Sun', 8.03, 1);

-- Альбом Joyride
INSERT INTO Track(name,	duration, id_album)
VALUES('Joyride', 4.30, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Hotblooded', 3.23, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Fading Like a Flower', 3.54, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Knockin on Every Door', 4.00, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Spending My Time', 4.39, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Watercolours in the Rain', 3.39, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('The Big L', 4.29, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('(Do You Get) Excited?', 4.18, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Small Talk', 3.54, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Physical Fascination', 3.31, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Things Will Never Be the Same', 4.29, 2);
INSERT INTO Track(name,	duration, id_album)
VALUES('Perfect Day', 4.06, 2);

-- Альбом Hatebreeder
INSERT INTO Track(name,	duration, id_album)
VALUES('Warheart', 4.08, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('Silent Night, Bodom Night', 3.12, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('Hatebreeder', 4.19, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('Bed of Razors', 3.57, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('Towards Dead End', 4.54, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('Black Widow', 3.58, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('Wrath Within', 3.52, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('Children of Bodom', 5.13, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('Downfall', 4.33, 3);
INSERT INTO Track(name,	duration, id_album)
VALUES('No Commands', 4.44, 3);

-- Альбом The Division Bell
INSERT INTO Track(name,	duration, id_album)
VALUES('Cluster One', 5.58, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('What Do You Want from Me', 4.21, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('Poles Apart', 7.04, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('Marooned', 5.29, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('A Great Day for Freedom', 4.17, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('Wearing the Inside Out', 6.49, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('Take It Back', 6.12, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('Coming Back to Life', 6.19, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('Keep Talking', 6.11, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('Lost for Words', 5.14, 4);
INSERT INTO Track(name,	duration, id_album)
VALUES('High Hopes', 8.31, 4);

-- Сборники
INSERT INTO Collection(name, year)
VALUES('Guitar perfect', 2018);
INSERT INTO Collection(name, year)
VALUES('Psychodelic', 2020);
INSERT INTO Collection(name, year)
VALUES('Ballads', 2022);
INSERT INTO Collection(name, year)
VALUES('My favorite', 2024);

-- Сборник Guitar perfect
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(5, 1);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(25, 1);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(36, 1);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(43, 1);

-- Сборник Psychodelic
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(6, 2);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(8, 2);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(36, 2);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(38, 2);

-- Сборник Ballads
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(14, 3);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(15, 3);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(43, 3);

-- Сборник My favorite
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(11, 4);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(21, 4);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(31, 4);
INSERT INTO TrackCollection(id_track, id_collection)
VALUES(41, 4);