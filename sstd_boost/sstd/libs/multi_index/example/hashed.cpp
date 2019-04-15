/* Boost.MultiIndex example of use of hashed indices.
 *
 * Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#if !defined(NDEBUG)
#define BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING
#define BOOST_MULTI_INDEX_ENABLE_SAFE_MODE
#endif

#include <sstd/boost/multi_index_container.hpp>
#include <sstd/boost/multi_index/hashed_index.hpp>
#include <sstd/boost/multi_index/member.hpp>
#include <sstd/boost/multi_index/ordered_index.hpp>
#include <sstd/boost/tokenizer.hpp>
#include <iomanip>
#include <iostream>
#include <string>

using boost::multi_index_container;
using namespace boost::multi_index;

/* word_counter keeps the ocurrences of words inserted. A hashed
 * index allows for fast checking of preexisting entries.
 */

struct word_counter_entry
{
  std::string  word;
  unsigned int occurrences;

  word_counter_entry(std::string word_):word(word_),occurrences(0){}
};

/* see Compiler specifics: Use of member_offset for info on
 * BOOST_MULTI_INDEX_MEMBER
 */

typedef multi_index_container<
  word_counter_entry,
  indexed_by<
    ordered_non_unique<
      BOOST_MULTI_INDEX_MEMBER(word_counter_entry,unsigned int,occurrences),
      std::greater<unsigned int> /* sorted beginning with most frequent */
    >,
    hashed_unique<
      BOOST_MULTI_INDEX_MEMBER(word_counter_entry,std::string,word)
    >
  >
> word_counter;

/* utilities */

template<typename T>
struct increment
{
  void operator()(T& x)const{++x;}
};

typedef boost::tokenizer<boost::char_separator<char> > text_tokenizer;

int main()
{
  /* boostinspect:noascii */

  std::string text=
    "En un lugar de la Mancha, de cuyo nombre no quiero acordarme, no ha "
    "mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga "
    "antigua, rocín flaco y galgo corredor. Una olla de algo más vaca que "
    "carnero, salpicón las más noches, duelos y quebrantos los sábados, "
    "lantejas los viernes, algún palomino de añadidura los domingos, "
    "consumían las tres partes de su hacienda. El resto della concluían sayo "
    "de velarte, calzas de velludo para las fiestas, con sus pantuflos de lo "
    "mesmo, y los días de entresemana se honraba con su vellorí de lo más "
    "fino. Tenía en su casa una ama que pasaba de los cuarenta, y una "
    "sobrina que no llegaba a los veinte, y un mozo de campo y plaza, que "
    "así ensillaba el rocín como tomaba la podadera. Frisaba la edad de "
    "nuestro hidalgo con los cincuenta años; era de complexión recia, seco "
    "de carnes, enjuto de rostro, gran madrugador y amigo de la caza. "
    "Quieren decir que tenía el sobrenombre de Quijada, o Quesada, que en "
    "esto hay alguna diferencia en los autores que deste caso escriben; "
    "aunque, por conjeturas verosímiles, se deja entender que se llamaba "
    "Quejana. Pero esto importa poco a nuestro cuento; basta que en la "
    "narración dél no se salga un punto de la verdad.";

  /* feed the text into the container */

  word_counter   wc;
  text_tokenizer tok(text,boost::char_separator<char>(" \t\n.,;:!?'\"-"));
  unsigned int   total_occurrences=0;
  for(text_tokenizer::iterator it=tok.begin(),it_end=tok.end();
      it!=it_end;++it){
    /* Insert the word into the container. If duplicate, wit will point to
     * the preexistent entry.
     */

    ++total_occurrences;
    word_counter::iterator wit=wc.insert(*it).first;

    /* Increment occurrences.
     * In a lambda-capable compiler, this can be written as:
     *   wc.modify_key(wit,++_1);
     */

    wc.modify_key(wit,increment<unsigned int>());
  }

  /* list words by frequency of appearance */

  std::cout<<std::fixed<<std::setprecision(2);
  for(word_counter::iterator wit=wc.begin(),wit_end=wc.end();
      wit!=wit_end;++wit){
    std::cout<<std::setw(11)<<wit->word<<": "
             <<std::setw(5) <<100.0*wit->occurrences/total_occurrences<<"%"
             <<std::endl;
  }

  return 0;
}
