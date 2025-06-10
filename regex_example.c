#include <regex.h>
#include <stdio.h>
#include <string.h>

void regex_search(const char *pattern, const char *str) {
  regex_t regex_buffer;
  int ret;

  if ((regcomp(&regex_buffer, pattern, 0)) != 0) {
    printf("Regex compilation failed\n");
    return;
  }

  int match_result;
  regmatch_t pmatch;

  if ((regexec(&regex_buffer, str, 1, &pmatch, 0)) != 0) {
    printf("Result for '%s' in '%s': No match found\n", pattern, str);
    return;
  }

  // TODO: use regerror

  int match_length = pmatch.rm_eo - pmatch.rm_so;
  char outstr[match_length + 1];
  strncpy(outstr, str + pmatch.rm_so, match_length);
  printf("Result for '%s' in '%s': '%s'\n", pattern, str, outstr);

  regfree(&regex_buffer);
}

int main() {
  char *pattern = "[h|H]ello";
  char *test1 = "hello world\0";
  char *test2 = "Hello world\0";
  char *test3 = "one two three\0";

  regex_search(pattern, test1);
  regex_search(pattern, test2);
  regex_search(pattern, test3);

  return 0;
}
