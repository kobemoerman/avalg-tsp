#include "utils.hpp"

/**
  * @Info:    Builds a distance matrix between all vertices.
  * @Return:  2D integer array.
  */
int **distance_matrix(int n, vector<city_t> v)
{
  int i, j, d;

  int **m = init2Darray(n);

  for (i = 0; i < n; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      d = eucledian(v[i], v[j]);
      m[i][j] = d, m[j][i] = d;
    }
  }

  return m;
}

/**
  * @Info:    Calculate the eucledian distance between two points.
  * @Return:  Rounded distance.
  */
int eucledian(city_t city, city_t neighbour)
{
  float dx, dy;

  dx = city.x - neighbour.x;
  dy = city.y - neighbour.y;

  return (int)(round(sqrt(dx * dx + dy * dy)));
}

/**
  * @Info:    Read the input from the command line. The first line is the number of cities. The following lines contain a pair of (x,y) coordinates.
  * @Return:  The input vector.
  */
vector<city_t> read_stdin(int &n)
{
  int i;
  city_t c;
  vector<city_t> v;

  cin >> n;

  for (i = 0; i < n; i++)
  {
    cin >> c.x >> c.y;
    v.push_back(c);
  }

  return v;
}

/**
  * @Info:    Prints the path from the vector.
  */
void print_path(vector<int> path, int **g)
{
  for (auto p : path)
    cout << p << endl;
}

/**
  * @Info:    Allocates memory for a 2D array.
  * @Return:  2D integer array.
  */
int **init2Darray(int n)
{
  int i;
  int **arr = (int **)malloc(n * sizeof(int *));
  for (i = 0; i < n; i++)
  {
    arr[i] = (int *)malloc(n * sizeof(int));
  }
  return arr;
}

/**
  * @Info:    Prints a 2D array.
  */
void print_matrix(int n, int **arr)
{
  int i, j;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      cout << arr[i][j] << ' ';
    }
    cout << endl;
  }
}
