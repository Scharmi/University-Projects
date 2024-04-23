def trap_rain(arr):
    n = len(arr)
    l = 0
    r = n - 1
    pref_max = 0
    suf_max = 0
    res = 0
    while l <= r:
        if pref_max <= suf_max:
            res += max(0, pref_max - arr[l])
            pref_max = max(pref_max, arr[l])
            l += 1
        else:
            res += max(0, suf_max - arr[r])
            suf_max = max(suf_max, arr[r])
            r -= 1
    return res

#Example
arr = [2, 1, 3, 0, 1]
print(trap_rain(arr))