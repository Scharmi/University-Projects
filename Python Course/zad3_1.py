class anagramDictionary:
    def __init__(self):
      self.sortedDictionary = {}
    def add(self, s: str):
      if(self.sortedDictionary.get(''.join(sorted(s))) != None):
        self.sortedDictionary[''.join(sorted(s))].add(s)
      else:
        self.sortedDictionary[''.join(sorted(s))] = {s}
    def get(self, s:str):
      if(self.sortedDictionary.get(''.join(sorted(s))) != None):
        return self.sortedDictionary[''.join(sorted(s))]
      else:
        return {}
D = anagramDictionary()