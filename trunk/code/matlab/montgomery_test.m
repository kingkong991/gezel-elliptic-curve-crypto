function bin = montgomery_test(x, y, n)
% Test file for the montgomery_bit_serial function

x = dec2bin(x);
y = dec2bin(y);

k = numel(dec2bin(n));
z = dec2bin(mod(2^(2*k), n));

n = dec2bin(n);

X = montgomery_bit_serial(x, z, n);
Y = montgomery_bit_serial(y, z, n);

A = montgomery_bit_serial(X, Y, n);

bin = montgomery_bit_serial(A, ['1'], n)
dec = bin2dec(bin)