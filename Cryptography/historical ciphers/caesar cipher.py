"""
	Расшифровать криптограмму Цезаря (неалфавитные
символы (пробелы, знаки препинания, цифры) – не преобразуются.).

"""

text = 'Нгн ргцнг нултхсёугчлв ескрлног тсфоз чцржгпзрхгоярюш угдсх гпзулнгрфнсёс пгхзпгхлнг л аознхусхзшрлнг Носжг Ызррсрг (1916–2001).'

alphabet = ['а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я']
c_alphabet = ['А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я']
shift = int(input("What is your shift? "))

def caesar(text, shift):
    result_text = ""
    for i in range(len(text)):
        if text[i] in alphabet or text[i] in c_alphabet:
            if text[i].isupper() == True:
                for j in range(len(alphabet)):
                    if text[i] == c_alphabet[j]:
                        if i < 0:
                            result_text += c_alphabet[j+30]
                        else:
                            result_text +=  c_alphabet[j-shift]
            else:
                for j in range(len(alphabet)):
                    if text[i] == alphabet[j]:
                        if i < 0:
                            result_text += alphabet[j + 30]
                        else:
                            result_text += alphabet[j - shift]
        else:
            result_text += text[i]
    return result_text
print(text)
print(caesar(text, shift))
