from itertools import product

elements = ["cmd", "r1", "r2", "r3", "r4", "p", "a"]

# Générer toutes les combinaisons possibles
combinations = [list(combo) for combo in product(elements, repeat=len(elements))]

# Supprimer les combinaisons dont le premier élément est 'a'
combinations = [combo for combo in combinations if combo[0] != 'a']

# Afficher les combinaisons
for combo in combinations:
    print(combo)

