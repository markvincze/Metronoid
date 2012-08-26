template <typename T> int sgn(T val) {
	if(val < T(0))
	{
		return -1;
	}
	else
	{
		return 1;
	}
}