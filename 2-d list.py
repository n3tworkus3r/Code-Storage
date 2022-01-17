a = [[0]*30]*30
for i in range(len(a)):
    print("[", end="")
    for j in range(len(a[i])):
        print(a[i][j], end = ',')
    print("]")
c = input("Ожидание завершения")
print()

print(a)