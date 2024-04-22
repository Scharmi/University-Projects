#\uczniowie{Jakub Biekionis, \\Dagna Czubla, \\Jan Skiba}

#Read the file and sord alphabetically names inside every \uczniowie{}.



import re

def cast_polish_letters(name):
    #Cast polish letters to their english equivalents.
    name = name.replace("ą", "azzzzzz")
    name = name.replace("ć", "czzzzzz")
    name = name.replace("ę", "ezzzzzz")
    name = name.replace("ł", "lzzzzzz")
    name = name.replace("ń", "nzzzzzz")
    name = name.replace("ó", "ozzzzzz")
    name = name.replace("ś", "szzzzzz")
    name = name.replace("ż", "zzzzzzz")
    name = name.replace("ź", "zzzzzzz")
    name = name.replace("Ą", "Azzzzzz")
    name = name.replace("Ć", "Czzzzzz")
    name = name.replace("Ę", "Ezzzzzz")
    name = name.replace("Ł", "Lzzzzzz")
    name = name.replace("Ń", "Nzzzzzz")
    name = name.replace("Ó", "Ozzzzzz")
    name = name.replace("Ś", "Szzzzzz")
    name = name.replace("Ż", "Zzzzzzz")
    name = name.replace("Ź", "Zzzzzzz")
    return name

def sort_names(uczniowie_tag):
    #Remove \uczniowie{}.
    uczniowie_tag = uczniowie_tag[11:-1]
    #Split the names.
    names = uczniowie_tag.split(", \\\\")
    #Sort the names by surname.
    names.sort(key=lambda x: cast_polish_letters(x.split()[1]))
    #Join the names.
    names = ", \\\\".join(names)
    #If there are more than 10 newlines in names, remove newlines.
    if names.count("\\\\") > 10:
        names = names.replace("\\\\", "")
    #Return the tag.
    return "\\uczniowie{" + names + "}"

with open("podziekowania.tex") as f:
    data = f.read()
#Find all occurences of \uczniowie{} and sort the names inside each tag.
uczniowie = re.findall(r"\\uczniowie\{.*?\}", data)
for i in range(len(uczniowie)):
    data = data.replace(uczniowie[i], sort_names(uczniowie[i]))

print(data)