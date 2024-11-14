import random
import string

def random_string(length):
    return ''.join(random.choices(string.ascii_uppercase + " ", k=length))

strings_data = [
    (random_string(10), random_string(10)),  # 10, 10 characters
    (random_string(16), random_string(18)),  # 16, 18 characters
    (random_string(22), random_string(20)),  # 22, 20 characters
    (random_string(32), random_string(32)),  # 32, 32 characters
    (random_string(44), random_string(40)),  # 44, 40 characters
    (random_string(60), random_string(64))  # 60, 64 characters
]

with open("strings.dat", "w+") as result_f:
    for str1, str2 in strings_data:
        result_f.writelines([f"\"{str1}\",\"{str2}\"", "\n"])

result_f.close()
