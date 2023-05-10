#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
     char *id;
     int weight;
};

typedef struct package package;

struct post_office
{
     int min_weight;
     int max_weight;
     package *packages;
     int packages_count;
};

typedef struct post_office post_office;

struct town
{
     char *name;
     post_office *offices;
     int offices_count;
};

typedef struct town town;

void print_office_packages(post_office office)
{
     for (int i = 0; i < office.packages_count; i++)
     {
          printf("\t\t%s\n", office.packages[i].id);
     }
}

void print_all_packages(town t)
{
     printf("%s:\n", t.name);
     for (int i = 0; i < t.offices_count; i++)
     {
          printf("\t%d:\n", i);
          print_office_packages(t.offices[i]);
     }
}

void send_all_acceptable_packages(town *source, int source_office_index, town *target, int target_office_index)
{
     post_office *source_office, *target_office;
     package *back;
     int i, back_count;

     source_office = &(source->offices[source_office_index]);
     target_office = &(target->offices[target_office_index]);
     back = malloc(source_office->packages_count * sizeof(package));
     back_count = 0;

     for(i = 0; i < source_office->packages_count; i++)
     {
          package to_be_sent = source_office->packages[i];
          
          if ((to_be_sent.weight <= target_office->max_weight) && (to_be_sent.weight >= target_office->min_weight))
          {
               target_office->packages_count += 1;
               target_office->packages = realloc(target_office->packages, (target_office->packages_count) * sizeof(package));
               target_office->packages[target_office->packages_count - 1] = to_be_sent;
          }
          else
          {
               back[back_count] = to_be_sent;
               back_count += 1;
          }
     }
     back = realloc(back, (back_count) * sizeof(package));
     source_office->packages = back;
     source_office->packages_count = back_count;
}

int count_town_packages(town t, int office_count)
{
     int packages_sum = 0;
     for (int i = 0; i < office_count; i++)
     {
          packages_sum += t.offices[i].packages_count;
     }

     return (packages_sum);
}

town town_with_most_packages(town *towns, int towns_count)
{
     town t = towns[0];
     int packages_1, packages_2;
     packages_1 = count_town_packages(towns[0], towns[0].offices_count);
     for (int i = 1; i < towns_count; i++)
     {
          packages_2 = count_town_packages(towns[i], towns[i].offices_count);
          if (packages_2 > packages_1)
          {
               packages_1 = packages_2;
               t = towns[i];
          }
     }
     return (t);
}

town *find_town(town *towns, int towns_count, char *name)
{
     town *town_found = NULL;
     for (int i = 0; i < towns_count; i++)
     {
          if (strcmp(towns[i].name, name) == 0)
          {
               town_found = &towns[i];
               break;
          }
     }
     return (town_found);
}

int main()
{
     int towns_count;
     scanf("%d", &towns_count);
     town *towns = malloc(sizeof(town) * towns_count);
     for (int i = 0; i < towns_count; i++)
     {
          towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
          scanf("%s", towns[i].name);
          scanf("%d", &towns[i].offices_count);
          towns[i].offices = malloc(sizeof(post_office) * towns[i].offices_count);
          for (int j = 0; j < towns[i].offices_count; j++)
          {
               scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
               towns[i].offices[j].packages = malloc(sizeof(package) * towns[i].offices[j].packages_count);
               for (int k = 0; k < towns[i].offices[j].packages_count; k++)
               {
                    towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                    scanf("%s", towns[i].offices[j].packages[k].id);
                    scanf("%d", &towns[i].offices[j].packages[k].weight);
               }
          }
     }
     int queries;
     scanf("%d", &queries);
     char town_name[MAX_STRING_LENGTH];
     while (queries--)
     {
          int type;
          scanf("%d", &type);
          switch (type)
          {
          case 1:
               scanf("%s", town_name);
               town *t = find_town(towns, towns_count, town_name);
               print_all_packages(*t);
               break;
          case 2:
               scanf("%s", town_name);
               town *source = find_town(towns, towns_count, town_name);
               int source_index;
               scanf("%d", &source_index);
               scanf("%s", town_name);
               town *target = find_town(towns, towns_count, town_name);
               int target_index;
               scanf("%d", &target_index);
               send_all_acceptable_packages(source, source_index, target, target_index);
               break;
          case 3:
               printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
               break;
          }
     }
     return 0;
}
