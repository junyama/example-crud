
CREATE TABLE AppUser (
    id          INTEGER PRIMARY KEY,
    username    VARCHAR UNIQUE,
    email       VARCHAR UNIQUE,
    password    VARCHAR,
    role        VARCHAR,
    saveImage   VARCHAR
);

INSERT INTO AppUser
(username, email, password, role, saveImage) VALUES ('admin', 'admin@domain.com', 'admin', 'ROLE_ADMIN', 'false');
