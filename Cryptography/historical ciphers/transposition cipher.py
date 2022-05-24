"""
	Реализовать схему шифрования посредством постолбцового
варианта маршрутной транспозиции. Входные параметры: сообщение, ключ (количество строк и столбцов
в прямоугольнике, используемом для шифрования). Выходные параметры: шифртекст.
	Реализовать схему расшифрования посредством постолбцового
варианта маршрутной транспозиции. Входные параметры: шифртекст, ключ (количество строк и столбцов
в прямоугольнике, используемом для шифрования). Выходные параметры: открытый текст.

"""

text = "Без труда не выловишь рыбку из пруда"
def transposition_crypt(text):
    print('\n\n\nCRYPT:')
    template = ""
    for i in text:
        if i.isalpha(): # Проверка на букву
            template+= i # Удаление символов-разделителей из строки
    print(template)
    n = 2
    while len(template)%n!=0: # Пока остаток от деления не равен нулю
        n+=1 # Ищем делитель
    m = int(len(template)/n) # Получаем частное
    print("Размер матрицы:", n,'x', m)

    k = 0 # Итератор по строке-шаблону

    matrix = []
    for j in range(n):
        row = []
        for i in range(m):
            row.append(template[k])
            k+=1
        matrix.append(row)
    #print(matrix)

    for i in range(m):
        for j in range(n):
            print(matrix[j][i],end="")
    pass


cipher_text = "Биешзьтррыубдкауниезвпырлуодва"

def transposition_encrypt(cipher_text):
    print('\n\n\nDECRYPT:')
    print(cipher_text)
    n = 2
    while len(cipher_text) % n != 0:  # Пока остаток от деления не равен нулю
        n += 1  # Ищем делитель
    m = int(len(cipher_text) / n)  # Получаем частное
    print("Размер матрицы дешифрования:", n, 'x', m)

    k = 0  # Итератор по строке-шаблону

    matrix = []
    for j in range(m):
        row = []
        for i in range(n):
            row.append(cipher_text[k])
            k += 1
        matrix.append(row)
    #print(matrix)

    print("\nРасшифрованное сообщение:")
    for i in range(n):
        for j in range(m):
            print(matrix[j][i], end="")
    pass


transposition_crypt(text)
transposition_encrypt(cipher_text)