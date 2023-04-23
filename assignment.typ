#set par(justify: true)
#set text(
  font: "Latin Modern Roman",
  size: 9.5pt,
)

#set page(
  paper: "a4",
  header:[
    #set align(center)
    = Zadání semestrální práce B35APO
  ],
  
  footer:[
    #set align(left)
    Praha, léto 2023
    #set align(center)
    #counter(page).display(
      "1",
    )
  ],
  
)


== Tým
- Rozálie Bílková --- bilkoroz\@fel.cvut.cz
- Jakub Adamec ---  adamej14\@fel.cvut.cz


== Návrh na práci
Desková hra Ubongo. Hráč má k dispozici zásobník různě tvarovaných dílků
a hrací desku s překážkami (zdmi). Jeho úkolem je umístit všechny dílky na hrací
plochu tak, aby využil všechny dílky a hrací plocha byla celá zaplněná, přičemž
žádný dílek nesmí vyčnívat nebo překrývat jiný/překrývat zeď, v co nejkratším čase.

Displej bude využit pro zobrazování hracího pole, zobrazení všech dostupných dílků
pro danou mapu a jejich následný přesun na hrací plochu. Při vybírání dílků bude mít vybraný dílek
okolo sebe zvýrazněnou hranici, aby šlo lépe určit, který dílek je právě zvolen.
Dílky samy o sobě mohou klidně být barevné.

Diody budou použit pro nápovědu. Program nejdříve určí správné tahy pro danou mapu
a počtem rozsvícených diod může naznačovat, jestli je daný dílek správně natočený či ne.

Výstup textu na displej se dá využít pro skóre. Plus nějaké menu jako *Nová hra* a *Konec*.

Pokud bude čas, tak přes SSH bychom mohli udělat volbu obtížnosti. To by se dalo považovat za 
periférii raw terminal vstup. Obtížnost znamená velikost mapy, a tedy počet dílků k odehrání.

== Použité periférie 
- RGB diody
- LE displej
- výstup textu na grafický displej
- případně SSH raw terminal vstup

