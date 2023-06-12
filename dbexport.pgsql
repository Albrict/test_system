--
-- PostgreSQL database dump
--

-- Dumped from database version 15.3
-- Dumped by pg_dump version 15.3

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: faculties; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.faculties (
    faculty_id integer NOT NULL,
    faculty_name character varying(255) NOT NULL
);


ALTER TABLE public.faculties OWNER TO postgres;

--
-- Name: faculties_faculty_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.faculties_faculty_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.faculties_faculty_id_seq OWNER TO postgres;

--
-- Name: faculties_faculty_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.faculties_faculty_id_seq OWNED BY public.faculties.faculty_id;


--
-- Name: groups; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.groups (
    group_name character varying(255) NOT NULL,
    faculty_id integer
);


ALTER TABLE public.groups OWNER TO postgres;

--
-- Name: students; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.students (
    student_id integer NOT NULL,
    group_id character varying(255) NOT NULL,
    first_name character varying(255) NOT NULL,
    second_name character varying(255) NOT NULL,
    middle_name character varying(255)
);


ALTER TABLE public.students OWNER TO postgres;

--
-- Name: students_student_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.students_student_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.students_student_id_seq OWNER TO postgres;

--
-- Name: students_student_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.students_student_id_seq OWNED BY public.students.student_id;


--
-- Name: subjects; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.subjects (
    subject_id integer NOT NULL,
    subject_name character varying(255),
    faculty_id integer
);


ALTER TABLE public.subjects OWNER TO postgres;

--
-- Name: subjects_subject_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.subjects_subject_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.subjects_subject_id_seq OWNER TO postgres;

--
-- Name: subjects_subject_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.subjects_subject_id_seq OWNED BY public.subjects.subject_id;


--
-- Name: tests; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.tests (
    test_id integer NOT NULL,
    test_name character varying(255) NOT NULL,
    score integer NOT NULL,
    student_id integer NOT NULL,
    subject_id integer NOT NULL
);


ALTER TABLE public.tests OWNER TO postgres;

--
-- Name: tests_test_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.tests_test_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tests_test_id_seq OWNER TO postgres;

--
-- Name: tests_test_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.tests_test_id_seq OWNED BY public.tests.test_id;


--
-- Name: faculties faculty_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.faculties ALTER COLUMN faculty_id SET DEFAULT nextval('public.faculties_faculty_id_seq'::regclass);


--
-- Name: students student_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.students ALTER COLUMN student_id SET DEFAULT nextval('public.students_student_id_seq'::regclass);


--
-- Name: subjects subject_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.subjects ALTER COLUMN subject_id SET DEFAULT nextval('public.subjects_subject_id_seq'::regclass);


--
-- Name: tests test_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tests ALTER COLUMN test_id SET DEFAULT nextval('public.tests_test_id_seq'::regclass);


--
-- Data for Name: faculties; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.faculties (faculty_id, faculty_name) FROM stdin;
1	Факультет Программирования
2	Факультет Экономики
3	Факультет Математики
4	Факультет Дизайна
\.


--
-- Data for Name: groups; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.groups (group_name, faculty_id) FROM stdin;
ИСП 21-21	1
ЛГА 20-21	2
ДРА 22-23	3
ЛСЭ 21-21	4
\.


--
-- Data for Name: students; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.students (student_id, group_id, first_name, second_name, middle_name) FROM stdin;
1	ИСП 21-21	Александр	Фамильчено	Владимирович
2	ЛГА 20-21	Алексей	Ларский	Олегович
3	ДРА 22-23	Оксана	Леская	Алексеевна
4	ЛСЭ 21-21	Альберт	Фризенберг	\N
5	ИСП 21-21	Владимир	Миронов	Викторович
7	ИСП 21-21	Алексей	Карелин	Игоревич
17	ДРА 22-23	Джон	Лейдлоу	
18	ДРА 22-23	Альберт	Цорк	Дмиртриевич
33	ИСП 21-21	Владимир	Карелин	Игоревич
34	ЛГА 20-21	Артем	Лызенко	
\.


--
-- Data for Name: subjects; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.subjects (subject_id, subject_name, faculty_id) FROM stdin;
1	Дискретная математика	1
2	Рисование	4
3	Экономика	2
4	Математическая статистика	2
5	Высшая математика	3
6	Геометрия	3
\.


--
-- Data for Name: tests; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.tests (test_id, test_name, score, student_id, subject_id) FROM stdin;
21	example test	80	7	3
22	example test	40	7	3
23	example test	40	7	3
24	example test	40	7	3
25	example test	60	7	3
26	example test	60	34	3
27	example test	60	7	3
28	Тест Ш.А.Б.А.К.А	140	7	3
1	Тест №1	92	1	5
2	Тест №2	35	4	3
3	Тест №3	38	2	5
4	Тест №4	12	2	5
5	Тест №5	99	3	5
6	Тест №6	65	1	3
7	Тест №7	40	4	4
8	Тест №8	16	3	2
9	Тест №9	71	1	5
10	Тест №10	46	2	6
11	Тест №11	84	3	5
12	Тест №12	96	3	5
13	Тест №13	85	4	3
14	Тест №14	51	2	3
15	Тест №15	45	2	2
16	Тест №16	79	3	4
17	Тест №17	34	4	6
18	Тест №18	45	4	6
19	Тест №19	16	1	6
20	Тест №20	87	2	6
\.


--
-- Name: faculties_faculty_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.faculties_faculty_id_seq', 4, true);


--
-- Name: students_student_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.students_student_id_seq', 34, true);


--
-- Name: subjects_subject_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.subjects_subject_id_seq', 6, true);


--
-- Name: tests_test_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.tests_test_id_seq', 28, true);


--
-- Name: faculties faculties_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.faculties
    ADD CONSTRAINT faculties_pkey PRIMARY KEY (faculty_id);


--
-- Name: groups groups_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.groups
    ADD CONSTRAINT groups_pkey PRIMARY KEY (group_name);


--
-- Name: students students_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.students
    ADD CONSTRAINT students_pkey PRIMARY KEY (student_id);


--
-- Name: subjects subjects_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.subjects
    ADD CONSTRAINT subjects_pkey PRIMARY KEY (subject_id);


--
-- Name: tests tests_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tests
    ADD CONSTRAINT tests_pkey PRIMARY KEY (test_id);


--
-- Name: groups faculty_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.groups
    ADD CONSTRAINT faculty_id FOREIGN KEY (faculty_id) REFERENCES public.faculties(faculty_id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: students students_group_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.students
    ADD CONSTRAINT students_group_id_fkey FOREIGN KEY (group_id) REFERENCES public.groups(group_name);


--
-- Name: subjects subjects_faculty_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.subjects
    ADD CONSTRAINT subjects_faculty_id_fkey FOREIGN KEY (faculty_id) REFERENCES public.faculties(faculty_id);


--
-- Name: tests tests_subject_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tests
    ADD CONSTRAINT tests_subject_id_fkey FOREIGN KEY (subject_id) REFERENCES public.subjects(subject_id);


--
-- PostgreSQL database dump complete
--

