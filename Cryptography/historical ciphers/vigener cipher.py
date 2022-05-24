"""
	Расшифровать криптограмму Виженера, если для шифрования было
использовано слово-лозунг «шифр».
"""

text = "ачаякч шящдцрцы эш анбьб, и ьюшцэп – бр яюблэ."
#            0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32
alphabet = ['а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я']
key = "шифр"
cipher_text = ""

def vigener(text, key):
    temp = ""
    cipher = ""
    final_text = ""
    for i in text:
        if i.isalpha(): # Проверка на букву
            temp+= i # Удаление символов-разделителей из строки
    print(temp)

    while len(cipher) <= len(temp): # Составление строки-ключа
        cipher += key
    print(cipher)

    for i in range(len(temp)):
        #print( alphabet.index(temp[i]) ,'+' ,alphabet.index(cipher[i]))
        # Сумма по mod n - шифрование. Разность по mod n - дешифрование
        ind = (alphabet.index(temp[i]) - alphabet.index(cipher[i])) % len(alphabet)
        final_text += alphabet[ind]

        #while i < len(text):
        #   if final_text[i].isalpha() == False:

    print(final_text)
    pass

vigener(text, key)