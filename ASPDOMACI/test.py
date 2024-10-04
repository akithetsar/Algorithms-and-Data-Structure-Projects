elementi = ["(1)", "(2)", "(3)", "(4)", "(5)", "(6)", "Kenta", "Full", "Poker", "Jamb", "SUMA"]
print("Talon: ")
print("\tNa dole\t\tNa gore\t\tRučna")

matrica = [[0, 0, 0]]*11

for i in range(11):
    row_print_list = []
    for j in range(3):
        row_print_list.append(matrica[i][j])
    row_print_list = [str(x) for x in row_print_list]
    row_print = elementi[i] + '\t' + "\t\t".join(row_print_list)
    print(row_print)


