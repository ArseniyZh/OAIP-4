"""
На прямоугольном поле для игры в морской бой размером M×N расположено несколько прямоугольных кораблей. Корабли не
соприкасаются друг с другом. Ваша задача — определить всевозможные типы кораблей на поле и число кораблей каждого типа.
Два корабля относятся к одному типу, если их размеры совпадают (корабли, которые могут быть получены друг из друга
поворотом, также относятся к одному типу). Первая строка входных данных содержит два положительных числа M и N,
не превосходящих 1000, задающие размеры поля. Далее идет M строк, каждая из которых состоит из N символов.
Символ `1' означает, что соответствующая клетка поля занята кораблем, символ `0' — что свободна. Пробелов в строке нет.

Программа должна для каждого обнаруженного типа корабля вывести одну строку, содержащую три числа. Первые два числа
задают размеры корабля (первое число должно быть не меньше второго), третье число задает количество кораблей данного
типа на поле. Строки в выводе должны быть отсортированы по первому числу, затем по второму числу.


Пример входных данных
6 10
0111000011
0000011011
0100011000
0101011011
0100000000
0001111011
Пример выходных данных
1 1 1
2 1 2
2 2 2
3 1 2
3 2 1
4 1 1

Примечание:
В примере есть корабли [{0; 1}, {0, 3}] и [{2; 1}, {4; 1}], они имеют размер 3x1 и 1x3.
У них будет два общих типа (3, 1) и (1, 3). Первый корабль изначально имеет тип (3, 1), если его развернуть, то получим
тип (1, 3), но он не подходит под условие (первое число должно быть не меньше второго), поэтому считаем корабль только
для типа (3, 1). Второй корабль изначально имеет тип (1, 3), но он также не подходит под условие, поэтому считаем
второй корабль только для типа (3, 1).
"""
from typing import List, Union


class Ship:
    def __init__(self, width: int, height: int):
        self.width = width
        self.height = height


def create_field() -> List[List[int]]:
    """
    Функция для создания поля из ввода пользователя.
    """
    welcome_text = "Пример входных данных\n" \
                   "6 10\n" \
                   "0111000011\n" \
                   "0000011011\n" \
                   "0100011000\n" \
                   "0101011011\n" \
                   "0100000000\n" \
                   "0001111011\n"
    print(welcome_text)

    m, n = map(int, input().split(" "))

    field = []

    # Просим пользователя построчно ввести m строк длиной n символов
    while 1:
        if len(field) == m:
            break

        row = list(map(int, input()))
        if len(row) != n or (row.count(0) + row.count(1)) != n:
            print(f"Введите строку длиной {n}, состоящую из 0 и 1")
        else:
            field.append(row)
    return field


def find_ships(field: List[List[int]], ships: Union[List[Ship], None] = None) -> List[Ship]:
    if ships is None:
        ships = []

    # Ищем первый индекс отличный от нуля
    found = False
    first_index = [0, 0]
    for i, row in enumerate(field):
        for j in range(len(row)):
            if field[i][j] == 1:
                first_index = [i, j]
                found = True
                break
        if any(first_index):
            break
    if not found:  # Если индекс не был найден - поле пустое, возвращаем значение
        return ships

    row_index, column_index = first_index
    width, height = 0, 0

    # Переходим на координату x, y
    while True:
        height += 1
        row = field[row_index]
        cell = column_index

        # Подсчитываем ширину корабля в текущей строке
        while cell < len(row) and row[cell] == 1:
            field[row_index][cell] = 0  # Очищаем текущую клетку
            cell += 1
            width = cell - column_index

        # Переходим на следующую строку
        row_index += 1

        if row_index == len(field) or field[row_index][column_index] == 0:
            break

    # Добавляем корабль в список
    ship = Ship(width, height)
    ships.append(ship)

    if width + height != 2:  # Если корабль не размером 1x1
        # Добавляем развернутый корабль в список
        ship = Ship(height, width)
        ships.append(ship)

    return find_ships(field, ships)


def main():
    field = create_field()
    ships = find_ships(field)

    ships_dict = {}
    for ship in ships:
        key = (ship.width, ship.height)
        ships_dict[key] = ships_dict.get(key, 0) + 1

    for (width, height), count in sorted(ships_dict.items()):
        if width >= height:
            print(f"{width} {height} {count}")


if __name__ == "__main__":
    main()
