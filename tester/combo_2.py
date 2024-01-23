from itertools import product

class ComboInstance:
    def __init__(self, combo):
        self.combo = combo
        self.valid = self._is_valid()

    def _is_valid(self):
        return not self.combo[0] == 'a'

    def update_valid(self):
        self.valid = self._is_valid()

    def __str__(self):
        return f"{self.combo}, {self.valid}"

class ComboList:
    def __init__(self, elements):
        self.elements = elements
        self.combinations = [ComboInstance(combo) for combo in product(elements, repeat=len(elements))]

    def update_valid_for_all(self):
        for combo_instance in self.combinations:
            combo_instance.update_valid()

    def __str__(self):
        return "\n".join(str(combo_instance) for combo_instance in self.combinations)

# Générer toutes les combinaisons possibles
elements = ["cmd", "r1", "r2", "r3", "r4", "p", "a"]

# Créer une instance de la classe ComboList
combo_list = ComboList(elements)

# Ajuster l'attribut self.valid pour toutes les instances
combo_list.update_valid_for_all()

# Afficher les instances de la classe ComboList
print(combo_list)
