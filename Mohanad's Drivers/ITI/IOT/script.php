<?php
if(isset($_GET['status']))
{
    $myfile = fopen("status.txt","w");
    if($_GET['status'] == 'on')
    {
        header("Location: ON.html");
         fwrite($myfile,'1');
    }
    elseif($_GET['status'] == 'off')
    {
        header("Location: OFF.html");
        fwrite($myfile,'0');
    }
}
?>