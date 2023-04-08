# Practica 2
# Ej 1)
edades <- c(22, 22, 23, 24, 25, 25, 26, 27, 28, 29, 29, 29, 29, 29, 31, 31, 32, 33,
       34, 35, 35, 35, 36, 38, 39, 39, 42, 42, 44, 44, 45, 45, 45, 47, 48, 52,
       59, 66, 67, 69, 69)

# a) La variable de estudio es la edad de un sujeto, esta variable es
# cuantitativa discreta

# c)
# c-1)
length(edades)

# c-2)
media <- mean(edades)
mediana <- median(edades)

# Vector de edades sin repetir
edades_unicas <- unique(edades)
# Cantidad de veces que se repite una edad
max_repeticiones_edad <- tabulate(match(edades, edades_unicas))
moda <- edades_unicas[which.max(max_repeticiones_edad)]

cuartiles <- quantile(edades, c(0.25, 0.75))

# c-3)
rango <- max(edades) - min(edades)
ric <- cuartiles[2] - cuartiles[1]
s <- sd(edades)
var <- var(edades)

# c-4)
# Percentiles 10 y 50
quantile(edades, c(10, 50))

# c-5)
summary(edades)

# c-6)
boxplot(edades)

# c-7)
stem(edades)

# c-8)
hist(edades)

# Ejercicio 2
fumadores <- c(69.3, 56.0, 22.1, 47.6, 53.2, 48.1, 52.7, 34.4, 60.2, 43.8,
               23.2, 13.8)
no_fumadores <- c(28.6, 25.1, 26.4, 34.9, 29.8, 28.4, 38.5, 30.2, 30.6, 31.8,
                  41.6, 21.1, 36.0, 37.9, 13.9)

# a)
fumadores.media <- mean(fumadores)
no_fumadores.media <- mean(no_fumadores)

# b)
fumadores.sd <- sd(fumadores)
no_fumadores.sd <- sd(no_fumadores)

# c)
boxplot(fumadores, no_fumadores, names = c("Fumadores", "No fumadores"),
        ylab = "Tiempo para quedar dormido (minutos)",
        col = c("orange", "lightblue"))

# Ejercicio 4

data("chickwts")
attach(chickwts)

plot(feed, weight, xlab = "feed", ylab = "weight (g)")

detach(chickwts)
