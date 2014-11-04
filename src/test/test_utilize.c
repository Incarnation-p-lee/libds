static void
test_result_print(char *name, bool passed)
{
   char *msg = "Unknown Test Function";

   if (name) {
      msg = name;
   }

   if (passed) {
       fprintf(stdout, "  . [32mPass[0m ... %s\n", msg);
   } else {
       fprintf(stdout, "  . [31mFail[0m ... %s\n", msg);
   }

   return;
}
