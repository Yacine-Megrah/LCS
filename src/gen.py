import random
import string

def random_string(length):
    return ''.join(random.choices(string.ascii_uppercase + " ", k=length))

strings_data = [
    (random_string(10), random_string(10)),  # 10, 10 characters
    (random_string(22), random_string(20)),  # 10, 20 characters
    (random_string(44), random_string(40)),  # 20, 40 characters
    (random_string(80), random_string(82)),  # 40, 80 characters
    (random_string(158), random_string(160))  # 80, 160 characters
]

with open("strings.dat", "w+") as result_f:
    for str1, str2 in strings_data:
        result_f.writelines([f"{str1},{str2}", "\n"])

result_f.close()
