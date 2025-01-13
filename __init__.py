from kivy_ios.toolchain import CythonRecipe

class QuicklzRecipe(CythonRecipe):
    version='1.4.1'
    url = "https://github.com/redwolf010/pyquicklz/archive/refs/tags/1.4.1.tar.gz"
    library = "quicklz"
    depends = []
    
    def build_arch(self, arch):
        super().build_arch(arch)
        print(f"Building Quickly for architecture:{arch.arch}")
recipe = QuicklzRecipe()
