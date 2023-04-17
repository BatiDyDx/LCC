# Trabajo Practico - Estadistica Descriptiva

# Usamos el paquete xlsx para leer archivos de extension xls
# install.packages("xlsx")

library(xlsx)
setwd("~/lcc/pye/tp1")

arboles <- read.xlsx("Base7.xls", sheetName = "base", stringsAsFactors = T)
main.title <- "Analisis descriptivo de arboles en Ciudad de Buenos Aires"
fuente <- "Fuente: Censo Forestal Urbano Público, Buenos Aires, 2011"

attach(arboles)
par(cex.main = 1.2)
par(mai = c(1,1.5,1,1))

# Boxplot origen vs altura
plot(origen, altura, main = main.title, col = "lightblue",
     xlab = "Origen de Arboles", ylab = "Altura (m)")

mtext(fuente, side = 1, line = 4)


# Especie
title <- "Especies de arboles en Buenos Aires, 2011"
especies.exotico <- c("Álamo", "Eucalipto", "Fresno", "Ficus", "Casuarina")
especies.nativo <- c("Palo borracho", "Ceibo", "Jacarandá", "Acacia")
orden <- order(table(especie), decreasing = TRUE)
especie.freq = table(especie)[orden]
colors <- c()
for (nombre.especie in rownames(especie.freq)) {
  if (nombre.especie %in% especies.exotico) {
    colors <- c(colors, "lightgreen")
  } else {
    colors <- c(colors, "orange")
  }
}

# porcentajes <- round(table(especie)[orden] / length(especie), digits = 2) * 100
par()
barplot(especie.freq, col = colors, horiz = T, las = 1,
        xlab = "Frecuencia absoluta de especies", xlim = c(0,90),
        main = title, xaxt = "n")
axis(side = 1, at = seq(0,90,10), labels = seq(0,90,10))
legend(x = "topright", legend = c("Exótico", "Nativo/Autóctono"),
       fill = c("lightgreen", "orange"))

# Altura
# Promedio de altura por especie
promedio_alt_esp <- function (es) {
  return (round(mean(altura[arboles$especie == es]), digits = 1))
}

for (ff in levels(especie)) {
  print(paste(ff, ": ", promedio_alt_esp(ff)))
}

title <- "Altura de arboles urbanos en Buenos Aires, 2011"

hist(altura, right = T, col = "lightblue", main = title, xlab = "Altura (m)",
     ylab = "Frecuencia absoluta", freq = T)

# Poligonos
intervalos.izq <- seq(0,40,5)
tabla.intervalos <- table(cut(altura, breaks = c(intervalos.izq, 45), right = T))

# Poligono frecuencias
altura.prop = tabla.intervalos / length(altura)
plot(altura.prop, type = "l", main = title, col = "red", xlab = "Altura (m)",
     ylab = "Frecuencia relativa", xaxt = "n")

axis(1, at = (1:length(intervalos.izq)), labels = intervalos.izq)
abline(h = seq(0,0.25,0.05), lty = "dashed")

# Poligono acumulativo
altura.cumsum = cumsum(tabla.intervalos)
plot(altura.cumsum, type = "l", col= "blue", lwd = 2, xaxt = "n",
     xlab = "Altura (m)", ylab = "Frecuencia absoluta acumulada",
     main = title)
axis(1, at = (1:length(intervalos.izq)), labels = intervalos.izq)
abline(h = seq(0,350,50), lty = "dashed")

# Diametro
boxplot(diametro, col = "orange", xlab = "Diametro (cm)", horizontal = T,
        main = "Diametro de arboles en ciudad de Buenos Aires, 2011",
        ylim = c(0,200))

# Origen
title <- "Origen de arboles en Buenos Aires, 2011"

origen.freq <- table(origen)
origen.prop <- origen.freq / length(origen)
labs <- c()
for (orig in levels(origen)) {
  prop <- round(origen.prop[orig], digits = 2) * 100
  labs <- c(labs, paste(orig, "\n", prop, "%", sep = ""))
}

pie(origen.prop, labels = labs, col = c("lightgreen", "orange"),
    main = title)

barplot(origen.freq, col = "pink", main = title, ylim = c(0, 250))


# Brotes
# Histograma cant de brotes, intervalos irregulares
title <- "Brotes en el ultimo año de arboles en Buenos Aires, 2011"
#intervalos <- seq(0, 10, 2)
intervalos <- c(0, 2, 3, 4, 5, 7, 10)
hist(brotes, breaks = intervalos, main = title, col = "orange", right = F,
     xlab = "Cantidad de brotes", ylab = "Densidad", ylim = c(0,0.3))

# Grafico de bastones
plot(table(brotes), type = "h", col = "blue", xlab = "Numero de brotes",
     ylab = "Frecuencia absoluta", main = title)

# Poligono freq absoluta acumulada
brotes.freq <- table(cut(brotes, breaks = intervalos, right = F))
brotes.cumfreq <- c(0, cumsum(brotes.freq), 350)
plot(brotes.cumfreq, type = "s", xaxt = "n", col = "blue",
     xlab = "Cantidad de brotes", ylab = "Frecuencia absoluta acumulada",
     main = title)
x.labels <- 0:10
axis(side = 1, at = x.labels, labels = x.labels)
abline(h = seq(0, 350, 50), lty = "dashed")

# Inclinacion
title <- "Inclinacion positiva en arboles de Buenos Aires, 2011"

# Histograma
inclinacion.pos <- inclinacion[inclinacion > 0]
intervalos <- c(0,5,10,15,25,40)
hist(inclinacion.pos, breaks = intervalos, col = "lightblue", main = title,
     xlab = "Numero de brotes", ylab = "Densidad", ylim = c(0,0.08), xaxt = "n")

axis(side = 1, at = seq(0,40,5), labels = T)

# Tallo y hoja
stem(inclinacion.pos, scale = 0.75)

# Barras de categorias (inclinacion nula vs inclinacion pos.)
barplot(inclinacion.categorias, ylim = c(0, 250), col = "lightgreen",
        xlab = "Categorias de inclinacion", ylab = "Frecuencia absoluta",
        main = "Inclinacion de arboles en Buenos Aires, 2011", cex.lab = 1.2)


## BIVARIADOS
# Especies y origenes

