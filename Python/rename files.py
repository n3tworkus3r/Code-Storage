import os
import random

##### ПЕРЕМЕШИВАНИЕ С ПЕРЕИМЕНОВАНИЕМ #####

folder = "E:\\Media\\Steam screens"
os.chdir(folder)
print("DIRECTORY HAS OPEN: ", os.getcwd())
item_counter = 0
item_list = []
index = 0

for i in os.listdir(folder):
    item_counter += 1
    os.rename(i, "temp" + str(item_counter) + ".jpg")

for i in range(1, item_counter + 1):
    item_list.append(i)

random.shuffle(item_list)

for i in os.listdir(folder):
    os.rename(i, str(item_list[index]) + ".jpg")
    index += 1
    print(index * 100 / len(item_list))

############################################

####### УПОРЯДОЧЕННОЕ ПЕРЕИМЕНОВАНИЕ #######
"""
folder = "E:\\Media\\x\\PH"
item_index = 1

os.chdir(folder)

#print(os.getcwd())


for i in os.listdir(folder):
    os.rename(i, str(item_index)+".jpg")
    item_index+=1

"""

############################################

