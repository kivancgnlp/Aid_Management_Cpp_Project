# Aid_Management_Cpp_Project
Example C++ Project

# Compiling

Use the CMakeLists.txt file under src folder for compiling

# Sample output

Aid Management System
Date: 2022/03/31
Data file: No file
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit
> 7
****New/Open Aid Database****
Enter file name: data.dat
6 records loaded!
Aid Management System
Date: 2022/03/31
Data file: data.dat
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit
> 6
****Ship Items****
Shipping Order for 3 times saved!
Aid Management System
Date: 2022/03/31
Data file: data.dat
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
readme.md 4/7/2022
70 / 71
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit
> 1
****List Items****
ROW | SKU | Description | Have | Need | Price
| Expiry
-----+-------+-------------------------------------+------+------+--------
-+-----------
1 | 45678 | Sleeping Bags | 100 | 200 | 65.66
|
2 | 44444 | Flash lights | 399 | 400 | 65.66
|
3 | 12345 | Baby Formula | 145 | 200 | 33.99
| 2022/12/12
-----+-------+-------------------------------------+------+------+--------
-+-----------
Enter row number to display details or <ENTER> to continue:
>
Aid Management System
Date: 2022/03/31
Data file: data.dat
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit
> 0
Exiting Program!
File: data.dat
45678 Sleeping Bags 100 200 65.66
44444 Flash lights 399 400 65.66
12345 Baby Formula 145 200 33.99 221212
------------------------------------------------
File: shippingOrder.txt
Shipping Order, Date: 2022/03/31
ROW | SKU | Description | Have | Need | Price
| Expiry
-----+-------+-------------------------------------+------+------+--------
-+-----------
1 | 12113 | Hydrogen peroxide 100ml bottles | 300 | 300 | 3.99
|*2023/11/11
2 | 56789 | Tents and Blankets and pillows Tent | 2000 | 2000 | 65.66
|
3 | 11223 | Enfamil A+ | 38 | 38 | 38.99
readme.md 4/7/2022
71 / 71
|*2022/11/11
-----+-------+-------------------------------------+------+------+--------
-+-----------
