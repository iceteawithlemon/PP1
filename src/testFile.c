# include <stdio.h>
# include <assert.h>


int main()
{
  FILE *fp = fopen("exemple10.tsp", "r");
  assert(fp != NULL);
  char *str;
  while(fgets(str, 100, fp))
    puts(str);
  fclose(fp);
  return 0;
}
