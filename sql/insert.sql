INSERT INTO Groups (group_id, group_name)
VALUES
  (1, 'Group A'),
  (2, 'Group B'),
  (3, 'Group C'),
  (4, 'Group D');

INSERT INTO Faculties (faculty_id, faculty_name)
VALUES
  (1, 'Faculty of Arts'),
  (2, 'Faculty of Science'),
  (3, 'Faculty of Business'),
  (4, 'Faculty of Engineering');

INSERT INTO Students (student_id, student_name, group_id)
SELECT 
  generate_series(1, 12) AS student_id,
  'Student ' || generate_series(1, 10) AS student_name,
  (random() * 3 + 1)::integer AS group_id;

INSERT INTO Subjects (subject_id, subject_name, faculty_id)
SELECT 
  generate_series(1, 7) AS subject_id,
  'Subject ' || generate_series(1, 6) AS subject_name,
  (random() * 3 + 1)::integer AS faculty_id;

INSERT INTO Tests (test_id, test_name, score, student_id, subject_id)
SELECT 
  generate_series(1, 20) AS test_id,
  'Test ' || generate_series(1, 20) AS test_name,
  (random() * 100)::numeric(5, 2) AS score,
  (random() * 10 + 1)::integer AS student_id,
  (random() * 6 + 1)::integer AS subject_id;
