# Завдання

Задача 3:
Структура Викладач має наступні поля: ім’я, оцінка в кампусі, якість
лекцій, вчасність надання матеріалів тощо. Створити відсортовану “базу даних”
викладачів, в якій можна швидко перевіряти наявність потрібного викладача та
знаходити всіх викладачів на вказаному проміжку (між двома викладачами).

## Створити структуру T для зберігання об’єктів з характеристиками
відповідно до обраної задачі, обрати критерій для порівняння двох об’єктів
та перевантажити необхідні оператори.

## Реалізувати бінарне дерево пошуку:
- 	Створити базовий елемент дерева Node, що буде містити в собі дані
	та вказівники на двох нащадків – лівого та правого. За необхідності
	додати вказівник на батьківський вузол.

-	Створити структуру BinarySearchTree з основними методами бінарного дерева пошуку без балансування:
	-	insert(object) – додати новий елемент в дерево (без повторень)
	-	find(object) – перевірити наявність елемента в дереві
	-	erase(object) – видалити елемент з дерева
	-	size() – знайти кількість елементів в дереві

-	Реалізувати додаткові методи для роботи з деревом:
	-	print() – вивести всі елементи дерева (у відсортованому порядку)
	-	height() – знайти висоту дерева
	-	findInRange(minObject, maxObject) – знайти всі елементи в дереві напроміжку [minObject, maxObject], повернути їх кількість (або динамічний масив (vector) з цими елементами)

- 	Провести тестування, використавши вказану нижче функцію
 	testBinarySearchTree(). Перевірити правильність та швидкість роботи,
	порівнявши з готовим бібліотечним рішенням STL set.

## 4 Доповнене завдання (+5 балів)
Реалізувати префіксне дерево для роботи програми автодоповнення слів.
	-	Створити базовий елемент дерева Node, що буде містити хеш-таблицю
		(unordered_map), де ключ – це текстовий символ, значення – вказівник на
		відповідний Node, а також булеву помітку чи є цей вузол кінцем слова.
		Замість хеш-таблиці можна використати статичний або динамічний масив,
		дослідити оптимальність такого варіанту.
	- 	Створити структуру Trie та реалізувати основні методи префіксного дерева:
		-	insert(word) – додати нове слово в дерево
		-	findByPrefix(prefix) – знайти слова, що починаються на заданий префікс
		Зчитати з файлу всі існуючі слова та побудувати з ними префіксне дерево.
		Файл зі словами можна взяти тут:
		https://github.com/dwyl/english-words/raw/master/words_alpha.txt
		https://github.com/dwyl/english-words/blob/master/words_alpha.zip?raw=true
	-	Протестувати правильність роботи префіксного дерева, використавши
		різні префікси, що вводяться з клавіатури.

## Додаткові завдання
Доповнити реалізацію бінарного дерева пошуку з основного завдання:
	1. Реалізувати методи бінарного дерева пошуку для роботи з піддеревами:
		merge(tree1, tree2) об’єднати два дерева в одне
		split(tree, object) розділити бінарне дерево пошуку по ключу на два
		інших, в першому всі елементи < object, в другому >= object
		eraseRange(minObject, maxObject) видалити всі елементи дерева на
		проміжку [minObject, maxObject], використавши створені вище методи
	2. Реалізувати у BinarySearchTree логіку балансування по типу АВЛ-дерева
		або іншого збалансованого дерева (червоно-чорне дерево, splay дерево)