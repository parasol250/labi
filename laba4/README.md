На основе второй или третьей лабораторных работ создать десктопное приложение.
Разрешается использовать свою собственную идею для данной работы, т.е. не строго следовать наработкам из 2 и 3 лабораторных работ.
Главная идея - портирование консольного приложения в Windows Forms.

Основные функционал и задачи, которые необходимо реализовать:
1)	Минимально 2 окна.
2)	У неглавного окна сделать перегрузку конструктора, чтобы при разных сценариях работы изменялись визуальные отображения на форме.
3)	Сделать выгрузку из файла и сохранение в файл данных.
4)	Сделать добавление, изменение и удаление данных, ввод данных вручную (чтобы можно было импортировать данные не только из файла, но пользователь мог их сам добавить). Изменения, связанные с данными тремя функциями должны визуально отображаться.
5)	Реализовать сортировку данных.
6)	Реализовать проверку полей правильности вода. Реализовать другие проверки, на то, что пользователь своими действиями не нарушит работоспособность вашего приложения.
7)	Реализовать функционал, который был у вас изначально в консольном приложении.
8)	Классы с которыми вы работаете (где храните данные) должны быть в отдельном файле. В .h файлах производится только объявление
9)	Использовать DataGridView; OpenFileDialog.

Полученная программа - приложение в Windows Forms, использованный язык - С++/CLI. Из-за особенностей работы Windows Forms некоторые фрагменты кода были адаптированы под платформу .NET;
отдельно прописанной функции сортировки данных здесь нет - для этого удобно использовать встроенную функцию сортировки элемента DataGridView из панели элементов формы (двойной клик по шапке столбца).