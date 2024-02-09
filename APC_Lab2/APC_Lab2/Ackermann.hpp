template<int M, int N>
struct Ackermann 
{
	static const int value = Ackermann<M - 1, Ackermann<M, N - 1>::value>::value;
};

template<int M>
struct Ackermann<M, 0>
{
	static const int value = Ackermann<M - 1, 1>::value;
};

template<int N>
struct Ackermann<0, N>
{
	static const int value = N + 1;
};