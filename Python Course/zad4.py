import json

with open('makeup_data.json') as file:
    data = json.load(file)

# The average price of products with the tag 'vegan' vs the average price of all products
total_price_vegan = 0
count_vegan = 0
total_price = 0
count = 0

for item in data:
    if "Vegan" in item.get("tag_list", []):
        total_price_vegan += float(item.get("price", 0))
        count_vegan += 1
    if item.get("price") is not None:
        total_price += float(item.get("price", 0))
        count += 1
    average_price_vegan = total_price_vegan / count_vegan
    average_price = total_price / count

print(f"The average price of products with the tag 'vegan' is: {average_price_vegan}")
print(f"The average price of all products is: {average_price}\n")

# Average color of lipsticks

total_red = 0
total_green = 0
total_blue = 0
count = 0

for item in data:
    if item.get("product_type") == "lipstick":
        for color in item.get("product_colors",[]):
            hex_color = color.get("hex_value")
            if hex_color is not None:
                total_red += int(hex_color[1:3], 16)
                total_green += int(hex_color[3:5], 16)
                total_blue += int(hex_color[5:7], 16)
                count += 1
print(f"The average color of lipsticks is: " + '\033[38;2;'+ str(total_red//count) + ';' + str(total_green//count) +';'+ str(total_blue//count) +'mThis!\033[0m \n')

#Medians of price of products from each brand
brand_prices = {}

for item in data:
    brand = item.get("brand")
    price = item.get("price")
    
    if brand and price:
        if brand not in brand_prices:
            brand_prices[brand] = []
        brand_prices[brand].append(float(price))

for brand, prices in brand_prices.items():
    brand_prices[brand].sort()
    if len(brand_prices[brand]) % 2 == 0:
        median = brand_prices[brand][len(brand_prices[brand])//2] + brand_prices[brand][len(brand_prices[brand])//2-1]
        median /= 2
    else:
        median = brand_prices[brand][len(brand_prices[brand])//2]
    brand_prices[brand] = median
print("Median price of products from each brand:")
sorted_brand_prices = sorted(brand_prices.items(), key=lambda x: x[1])
for brand, median in sorted_brand_prices:
    print(f"{brand}: {median}")


