def check_matrix(matrix_row, M, N, rules):
    matrix = [*zip(*matrix_row)]
    for rule in rules:

        if '-' in rule:
            item1, item2 = rule.split('-')
            # If the rule is of the form "item1-item2", the items should not be in the same column
            item1_col = None
            item2_col = None
            for i, column in enumerate(matrix):
                if item1 in column:
                    item1_col = i
                if item2 in column:
                    item2_col = i
            # If one or both of the items haven't been placed yet, skip this rule
            if item1_col is not None and item2_col is not None and item1_col == item2_col:
                return False
        else:
            item1, item2 = rule.split('+')

            # If the rule is of the form "item1+item2", the items should be in the same column
            item1_col = None
            item2_col = None
            for i, column in enumerate(matrix):
                if item1 in column:
                    item1_col = i
                if item2 in column:
                    item2_col = i
            # If one or both of the items haven't been placed yet, skip this rule
            if item1_col is not None and item2_col is not None and item1_col != item2_col:
                return False
    # If all rules pass, the matrix is valid
    return True




matrica = [["Matija", "Maja", "Sanja"]]
for _ in range(1, 4):
    matrica.append([None] * 3)

matrica[1][1] = "zuta"
print(matrica)
uslovi = ["Maja+plava", "Maja-zuta", "Maja-zelena"]
print(check_matrix(matrica, 4,3, uslovi))


