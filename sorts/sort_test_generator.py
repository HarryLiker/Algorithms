import random

def main():
    test1_size = 10000;
    test2_size = 1000000;
    test3_size = 10000000;

    test1_file = open("test_01.txt", "w")
    for i in range(test1_size):
        test1_file.write(str(random.randint(0, 2**64)))
        test1_file.write('\n')
    test1_file.close()

    test2_file = open("test_02.txt", "w")
    for i in range(test2_size):
        test2_file.write(str(random.randint(0, 2**64)))
        test2_file.write('\n')
    test2_file.close()

    test3_file = open("test_03.txt", "w")
    for i in range(test3_size):
        test3_file.write(str(random.randint(0, 2**64)))
        test3_file.write('\n')
    test3_file.close()

main()
