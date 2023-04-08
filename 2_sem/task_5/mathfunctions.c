double Abs(double x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

double square_root(double value)
{
    double left = 1;
    double right = value;
    double eps = 0.000001;
    double middle, approx;
    do
    {
        middle = left + (right - left) / 2;
        approx = middle * middle;

        if (approx > value)
            right = middle;
        else
            left = middle;

    } while (Abs(approx - value) > eps);
    return middle;
}