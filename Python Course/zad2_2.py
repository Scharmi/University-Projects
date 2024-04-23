def find_edit_distance(w_1, w_2):
    current_distance = [j for j in range(len(w_2)+1)]
    updated_distance = [0 for j in range(len(w_2)+1)]
    
    for i in range(0, len(w_1)):
        updated_distance[0] = i
        for j in range(0, len(w_2)):
            if w_1[i] != w_2[j]:
                minimal_distance = min(1 + current_distance[j+1], 1 + updated_distance[j])
                updated_distance[j+1] = min(minimal_distance, 1 + current_distance[j])
            else:
                updated_distance[j+1] = current_distance[j]
        current_distance = [x for x in updated_distance]
    return current_distance[-1]

def find_shortest_edit_distance(word, dictionary):
    min_distance = float("inf")
    min_word = ""
    for word_2 in dictionary:
        distance = find_edit_distance(word, word_2)
        if distance < min_distance:
            min_distance = distance
            min_word = word_2
    return min_word

print(find_edit_distance("kot", "kastet"))
dictionary = {"akt", "koc", "sok", "python"}
print(find_shortest_edit_distance("kot", dictionary))