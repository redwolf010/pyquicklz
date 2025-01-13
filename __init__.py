from kivy_ios.toolchain import CythonRecipe

class QuicklzRecipe(CythonRecipe):
    version='1.4.1'
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
    def url(self):
        return "file://{}/quicklz".format(self.ctx.root_dir)
        
    url = url(self)
    library = "quicklz"
    depends = []
    
    def build_arch(self, arch):
        super().build_arch(arch)
        print(f"Building Quickly for architecture:{arch.arch}")
recipe = QuicklzRecipe()
