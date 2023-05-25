CREATE TABLE Groups (
  group_id INT PRIMARY KEY,
  group_name VARCHAR(255)
);

CREATE TABLE Students (
  student_id INT PRIMARY KEY,
  student_name VARCHAR(255),
  group_id INT,
  FOREIGN KEY (group_id) REFERENCES Groups(group_id)
);

CREATE TABLE Faculties (
  faculty_id INT PRIMARY KEY,
  faculty_name VARCHAR(255)
);

CREATE TABLE Subjects (
  subject_id INT PRIMARY KEY,
  subject_name VARCHAR(255),
  faculty_id INT,
  FOREIGN KEY (faculty_id) REFERENCES Faculties(faculty_id)
);

CREATE TABLE Tests (
  test_id INT PRIMARY KEY,
  test_name VARCHAR(255),
  score FLOAT,
  student_id INT,
  subject_id INT,
  FOREIGN KEY (student_id) REFERENCES Students(student_id),
  FOREIGN KEY (subject_id) REFERENCES Subjects(subject_id)
);
