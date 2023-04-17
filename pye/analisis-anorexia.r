# Ejercicio 1
setwd("~/lcc/pye")
cols <- c("Signo", "Sexo", "Edad", "Num.Visitas")
anorexia <- read.table(file = "anorexia.data", header = F,
                      skip = 1, col.names = cols,
                      colClasses = c("factor","factor","numeric","numeric"))
# Valores del factor Signo
# 0: dieta severa
# 1: hiperactividad
# 2: uso de laxantes
# 3: uso de ropa holgada

# Ejercicio 2
attach(anorexia)
Sexo

class(Sexo)
class(Signo)

summary(Sexo)
summary(Edad)

# Ejercicio 3
freq.abs <- table(Num.Visitas)

visitas <- 1:length(freq.abs)
total <- length(Num.Visitas)

freq.rel <- round(freq.abs / total, digits = 4)

freq.abs.ac <- cumsum(freq.abs)
freq.rel.ac <- round(cumsum(freq.rel), digits = 4)

data <- cbind(visitas, freq.abs, freq.rel, freq.abs.ac, freq.rel.ac)
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

# Ejercicio 4
# Tabla bivariada entre signo y sexo
tabla.ss <- table(Signo, Sexo)
total.filas <- apply(tabla.ss, 1, sum)
tabla.ss <- cbind(tabla.ss, total.filas)
total.cols  <- apply(tabla.ss, 2, sum)
tabla.ss <- rbind(tabla.ss, total.cols)

colnames(tabla.ss) <- c("Mujeres", "Hombres", "Total")
rownames(tabla.ss) <- c(labels, "Total")

# Ejercicio 5

tabla.signo <- table(Signo)

# b)
labels <- c("Dieta severa", "Hiperactividad", "Uso de laxantes",
  "Uso de ropa holgada")

pie(tabla.signo, main = c("PRINCIPAL SIGNO VISIBLE EN PACIENTES CON ANOREXIA",
                           "ARGENTINA, OCTUBRE 2012"),
    labels = labels, clockwise = TRUE)

# c)
percents <- round(tabla.signo / length(Signo), digits = 4) * 100
percents.str <- paste(as.character(percents), "%", sep = "")

percents.str = paste(labels, percents.str, sep = ":\n")

main.title <- c("PRINCIPAL SIGNO VISIBLE EN PACIENTES CON ANOREXIA",
           "ARGENTINA, OCTUBRE 2012")

pie(tabla.signo, main = title, labels = labels, clockwise = TRUE)

# d)
text = "Fuente: Asosiacion de Lucha contra la Bulimia y Anorexia"
mtext(text = text, side = 1, line = 2, cex = 0.8)

# Ejercicio 6

# b)
barplot(tabla.signo, main = main.title, horiz = TRUE, xlab = "Numero de pacientes",
        ylab = "Signo", xlim = c(0, max(tabla.signo) + 5), col = "lightpink")

# c)
ord <- order(tabla.signo, decreasing = T)
labels <- c()
barplot(tabla.signo[ord], names.arg = labels[ord],
        main = main.title, horiz = TRUE, xlab = "Numero de pacientes",
        ylab = "Signo", xlim = c(0, max(tabla.signo) + 5), col = "lightpink", 
        cex.names = 0.8, cex.axis = 1.2)

mtext(text, side = 1, line = 4, cex = 0.8)

# Ejercicio 7
data <- table(Sexo, Signo)
main.title[1] <- paste(main.title[1], "SEGUN SEXO")
colors <- c("#336633", "#FF3366")

par(cex.main = 0.8)
barplot(data, main = main.title, horiz = T, beside = T,
        xlab = "Numero de pacientes", names.arg = labels,
        col = colors)

legend(x = "topright", legend = c("F", "M"), fill = colors)
mtext(text, side = 1, line = 4)

# Ejercicio 8

par(cex.lab = 1.1)
# b)
main.title <- c("NUMERO DE VISITAS POR PACIENTE", "ARGENTINA, OCTUBRE 2012")
freq <- c(0, table(Num.Visitas), 0)

plot(x = 0:6, y = freq, type = "h", ylim = c(0,25),
     xlab = "Numero de visitas", ylab = "Frecuencia absoluta",
     main = main.title)

mtext(text, side = 1, line = 4)

# c)
prop.ac <- round(cumsum(freq) / length(Num.Visitas), digits = 4)
plot(x = 0:6, y = prop.ac, type = "s", xlab = "Numero de visitas",
     ylab = "Frecuencia relativa acumulada", main = main.title)
abline(h = seq(0, 1, 0.2), lty = "dotted", lwd = 0.75)
mtext(text, side = 1, line = 4)
