# Big Integer Library

A C++ library for performing arithmetic operations (+, –, ×, ÷, %, factorial, permutations, and combinations) on arbitrarily large integers using data structures.

## 🚀 Features

- Supports large integer arithmetic:
  - Addition (+)
  - Subtraction (–)
  - Multiplication (×)
  - Division (÷)
  - Modulus (%)
- Supports advanced operations:
  - Factorial (!)
  - Permutation (nPr)
  - Combination (nCr)
- Handles negative numbers
- Input and output through strings
- Fully implemented using basic C++ (no OOP)

## 📦 How It Works

Internally, numbers are stored as `vector<int>` in reverse order (least significant digit first). All operations mimic manual digit-wise arithmetic.

## 🛠️ Usage

Compile and run:

```bash
g++ main.cpp -o bigint
./bigint
```

Example interaction:

```
Enter first number: 12345678901234567890
Enter operator (+, -, *, /, %, !, P, C): *
Enter second number: 98765432109876543210
Result: 1219326311370217952237463801111263526900
```

## 🧠 Algorithms Used

- Addition/Subtraction: Digit-by-digit with carry/borrow
- Multiplication: Long multiplication (grade school method)
- Division/Modulus: Long division via repeated subtraction
- Factorial: Iterative multiply from 1 to n
- nPr/nCr: Calculated using factorial definitions

## 🔗 Repository Structure

```
├── main.cpp         # Main driver and logic
├── README.md        # Project documentation
```

## 🤝 Contributing

Contributions, issues, and suggestions are welcome! Fork the repo and open a pull request.

## 📄 License

This project is open source and available under the MIT License.
