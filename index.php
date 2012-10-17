<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Phoenix Legion Resources Calculator</title>
        <?php
            require_once('class.Resources.inc');
            require_once('class.EveOreDB.inc');
        ?>
    </head>
    <body>
        <?php
            $resources = new Resources();
            $resources->loadResources();
            
            //$resources->updateResources();
            
            $resources->display();
        ?>
    </body>
</html>
