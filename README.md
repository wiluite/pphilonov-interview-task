# pphilonov-interview-task

https://youtu.be/rRRyd4pYHRE  

### Задача:
На входе алгоритма массив, состоящий из 0 и 1.  
Первый элемент всегда 0, последний всегда 1.  
Элементы массива монотонно возрастают. Т.е. сначала идут одни 0, а потом одни 1.  
Нужно найти номер позиции, на которой стоит последний 0.  
0 0 0 0 0 1 1 1 1 1 1 1 1 1 1  
0 0 0 0 0 1 1 1  
0 0 1 1 1  
1  

### Решение:
Задача очень простая. Очевидно, что логарифмическая сложность здесь достаточна, поскольку исходная
последовательность представляет собой как бы частный случай отсортированной поседовательности, где
нули считать можно не итерационно, а используя свойство разности между двумя позициями в которых
стоят 0.

Рассуждаем так:
1. Позиция последнего 0 равна сумме всех нулей в массиве;-)
2. Деля пополам исходный массив (а затем продолжая это делать и далее), мы получаем подмассивы, 
каждый из которых:
    - либо начинается с 0 и заканчивается 0
    - либо начинается с 1 и заканчивается 1
    - либо представляет собой уменьшенный вариант исходного массива (нач. с 0, зак. 1)
    - других вариантов нет
3. Если получили первый вариант, то сумма нулей в нем равна числу элементов: сумму нужно вернуть 
вызывающей стороне, а подмассив исключить из дальнейшей обработки.
4. Если получили второй вариант, то вернуть нужно 0, а подмассив исключить из дальнейшей обработки.
5. Если получили третий вариант, то вызываем себя же дважды: для 2 новых подмассивов, складывая
возвращаемые значения и возвращая сумму вызывающей стороне.
6. Главная вызывающая сторона, таким образом, накапливает число нулей, возвращаемых всеми вызовами.

А весь алгоритм превращается в красивое рекурсивное решение в 6 строчек.
