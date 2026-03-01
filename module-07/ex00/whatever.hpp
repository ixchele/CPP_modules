#pragma  once

template <typename T>
void	swap(T &x, T &y) {
	T	tmp;
	tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
T	max(const T &x, const T &y) {
	return (x < y) ? y : x;
}

template <typename T>
T	min(T x, T y) {
	return (x > y) ? y : x;
}
