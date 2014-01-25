
showError = function(text)
{
    $("#output").
        css("background", "red").
        html(text);
}

check = function()
{
    var year = $("#year").val();
    if(!year || year.match(/\D/))
    {
        showError("Proszę podać wartość liczbową.");
        return;
    }
    year = parseInt(year);
    if(year < 33 || year > 2999)
    {
        showError("Proszę podać wartość z zakresu [33, 2999].");
        return;
    }
    
    $.ajax({
        dataType: "json",
        url: controlLocation + '?year=' + year,
        success: 
            function(data)
            { 
                $("#output").
                    css("background", "white").
                    html("Data wielkanocy w katolicyzmie: " + data["catholic"] + "<br/>" +
                         "Data wielkanocy w prawosławiu: " + data["ortodox"]
                    );
                    
               
            },
        error: 
            function (xhr, ajaxOptions, thrownError) 
            {
                showError("Błąd " + xhr.status + "<br />" + thrownError);
            }
    });
}