clc // limpia la consola
xdel(winsid()) // cierra ventanas graficas

// Definicion de la funcion
function y = f(x)
y = x.*x;
endfunction

// Calculo de la derivada utilizando diferencias finitas
function y = dfa(f,x,h)
y = (f(x+h) - f(x))./h;
endfunction

x = 1; // Punto donde vamos a evaluar la derivada
ih = (0:16)';
h = (10.^-ih); // Vector con los valores de h
df_approx = dfa(f,x,h); // Evaluaci ́on de la derivada por diferencias finitas
df_scilab = numderivative(f,x,[],order=1); // Derivada obtenida por numderivative
df_true = 2; // Valor verdadero de la derivada en x = 1

// Errores absolutos y relativos
err_abs = abs(df_approx - df_true);
err_rel = err_abs./abs(df_true);
err_abs_sci = abs(df_scilab - df_true);
err_rel_sci = err_abs_sci/abs(df_true);

// Grafica
plot(ih,log10(err_rel),'b*-'); // Grafica en escala logarıtmica en el eje y
title('Error relativo utilizando diferencias finitas');
xlabel('i');
ylabel('$log {10} (Err Rel)$');
plot(ih,log10(err_rel_sci*ones(length(ih),1)),'r-');
// Impresion de resultados en pantalla
tablevalue = [ih,h,df true*ones(length(h),1),df_approx,err_abs,err_rel];
mprintf(' %s\n',strcat(repmat('-',1,80)));
mprintf(' %4s %8s %12s %18s %14s %14s\n',...
'i', 'h','Der. exact','Der approx','Abs. error','Rel. error');
mprintf(' %s\n',strcat(repmat('-',1,80)));
mprintf(' %4d %8.1e %9.6e %18.10e %14.5e %14.5e\n',tablevalue);
mprintf(' %s\n',strcat(repmat('-',1,80)));
mprintf(' %4.1s %8s %9.6e %18.10e %14.5e %14.5e\n',...
' ', 'Scilab',[df_true,df_scilab,err_abs_sci,err_rel_sci]);
mprintf(' %s\n',strcat(repmat('-',1,80)));
