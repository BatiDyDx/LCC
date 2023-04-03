# Ej 1
path <- "~/Developer/lcc/pye/anorexia.data"
cols <- c("Signo", "Sexo", "Edad", "NumVisitas")
anorexia <- read.table(file = path, header = F, 
                      skip = 1, col.names = cols,
                      colClasses = c("factor","factor","numeric","numeric"))

attach(anorexia)

# Ej 2
freq.abs <- as.vector(table(NumVisitas))

nvisitas <- seq(1, length(freq.abs), 1)
total <- sum(freq.abs)

freq.rel <- round(freq.abs / total, digits = 4)

freq.abs.ac <- cumsum(freq.abs)
freq.rel.ac <- round(cumsum(freq.rel), digits = 4)

data <- cbind(nvisitas, freq.abs, freq.rel, freq.abs.ac, freq.rel.ac)
visitas.matrix <- as.data.frame(data)
# colnames(visitas.tabla) <- c("N. de Visitas", "Frec. Abs","Frec. Rel",
#                              "Frec. Abs. Ac", "Frec. Rel. Ac")

intervalos.edad = cut(Edad, breaks = seq(11, 35, 3), right = FALSE)
freq.abs <- as.vector(table(intervalos.edad))

freq.rel <- round(freq.abs / total, digits = 4)

freq.abs.ac <- cumsum(freq.abs)
freq.rel.ac <- round(cumsum(freq.rel), digits = 4)

data <- cbind(intervalos.edad, freq.abs, freq.rel, freq.abs.ac, freq.rel.ac)
visitas.matrix <- as.data.frame(data)
