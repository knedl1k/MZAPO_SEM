

#let project(title: "", authors: (), body) = {

  set document(author: authors, title: title)
  //set page(numbering: "1", number-align: center)
  set text(font: "New Computer Modern", lang: "cs", size:10.5pt)
  show math.equation: set text(weight: 400)


  set page(
    footer: [
      #set align(left)
      Praha, jaro 2023
      #set align(center)
      #set text(8pt)
      #counter(page).display(
        "1",
      )
    ]
  )

  // title
  align(center)[
    #block(text(weight: 700, 1.75em, title))
    B0B35APO - Architektura počítačů
  ]
  
  // author
  pad(
    top: 0.5em,
    bottom: 0.5em,
    x: 2em,
    grid(
      columns: (1fr,) * calc.min(2, authors.len()),
      gutter: 1em,
      ..authors.map(author => align(center, author)),
    ),
  )


  // body
  set par(justify: true)
  body

  
}
