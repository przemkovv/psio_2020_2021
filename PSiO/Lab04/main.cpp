
#include <iostream>
#include <vector>
#include <regex>
#include <string>


int main() {




    std::cout << "Hello " "World\n";


    std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean eros nunc, vehicula sed tincidunt ac, condimentum et turpis. Sed vestibulum risus lectus, id suscipit turpis scelerisque et. Vestibulum eros turpis, congue sed ante non, fermentum dapibus sem. Suspendisse ipsum nisl, suscipit eget viverra nec, bibendum ut odio. Ut nec pharetra elit, nec dignissim velit. Praesent sed mauris cursus, volutpat leo ac, fringilla dolor. Donec ut ornare ligula.\n"

"Fusce iaculis felis at risus sodales, et ornare dui laoreet. Suspendisse a massa interdum, placerat arcu quis, consequat tellus. Phasellus consequat massa odio, quis ultrices mauris dignissim nec. Phasellus interdum, eros vel faucibus ullamcorper, mi quam maximus turpis, eu hendrerit eros arcu a augue. Quisque ultricies viverra luctus. Sed consectetur, neque ut lacinia lacinia, sapien purus feugiat turpis, non feugiat diam urna nec nisi. Donec eget dictum nisl. Vestibulum et justo sit amet libero facilisis rhoncus in ut ex. Donec ut semper metus, ut feugiat libero. Duis varius odio eget nulla suscipit rhoncus. Fusce elementum non nunc a vestibulum. Pellentesque molestie iaculis vulputate.";

    std::string text2 = R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean eros nunc, vehicula sed tincidunt ac, condimentum et turpis. Sed vestibulum risus lectus, id suscipit turpis scelerisque et. Vestibulum eros turpis, congue sed ante non, fermentum dapibus sem. Suspendisse ipsum nisl, suscipit eget viverra nec, bibendum ut odio. Ut nec pharetra elit, nec dignissim velit. Praesent sed mauris cursus, volutpat leo ac, fringilla dolor. Donec ut ornare ligula.
Fusce iaculis felis at risus sodales, et ornare dui laoreet. Suspendisse a massa interdum, placerat arcu quis, consequat tellus. Phasellus consequat massa odio, quis ultrices mauris dignissim nec. Phasellus interdum, eros vel faucibus ullamcorper, mi quam maximus turpis, eu hendrerit eros arcu a augue. Quisque ultricies viverra luctus. Sed consectetur, neque ut lacinia lacinia, sapien purus feugiat turpis, non feugiat diam urna nec nisi. Donec eget dictum nisl. Vestibulum et justo sit amet libero facilisis rhoncus in ut ex. Donec ut semper metus, ut feugiat libero. Duis varius odio eget nulla suscipit rhoncus. Fusce elementum non nunc a vestibulum. Pellentesque molestie iaculis vulputate.)";


    std::cout << "Normal:\n" << text << "\n\n";
    std::cout << "Raw:\n" << text2 << "\n\n";


    std::string expression2 = "(\\w+)([,\\.]?)\\s?";
    std::string expression = R"((\w+)([,\.]?)\s?)";

    std::regex word_regex{expression};

   std::cout << "Czy jest dopasowanei w text2? ";
   std::cout << std::regex_search(text2, word_regex);
   std::cout << '\n';

   std::smatch m;

   auto begin = text2.cbegin();
   auto end = text2.cend();
   while (std::regex_search(begin, end, m, word_regex) == true) {
       std::cout << m[1].str() << '\n';
       begin = m.suffix().first;
   }




}





















