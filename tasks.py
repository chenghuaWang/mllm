import os
import re
import logging
from pathlib import Path
from typing import Dict

logging.basicConfig(
    format='%(asctime)s, %(levelname)s:%(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',
    level=logging.INFO,
)

ROOT_PATH = Path(os.path.dirname(os.path.abspath(__file__)))

GOOGLE_BENCHMARK_VERSION = 'v1.9.1'
GOOGLE_TEST_VERSION = 'v1.15.2'
FMT_VERSION = '11.1.2'

def wildcard_to_regex(pattern):
    # Escape all special characters in the pattern except for '*' and '?'
    regex = re.escape(pattern)
    # Replace '*' with '.*' to match any sequence of characters
    # Replace '?' with '.' to match any single character
    regex = regex.replace(r'\*', '.*').replace(r'\?', '.')
    # Return the full regex pattern with start and end anchors
    return f"^{regex}$"

def filter_files(directory, pattern, r=True):
    regex = re.compile(wildcard_to_regex(pattern))
    matched_files = []

    if r:
        for root, _, files in os.walk(directory):
            for file in files:
                if regex.match(file):
                    matched_files.append(os.path.join(root, file))
    else:
        for file in os.listdir(directory):
            if os.path.isfile(os.path.join(directory, file)) and regex.match(file):
                matched_files.append(os.path.join(directory, file))

    return matched_files

def override(func):
    def wrapper(*args, **kwargs):
        instance = args[0]
        super_class = instance.__class__.__bases__[0]
        if not hasattr(super_class, func.__name__):
            raise NotImplementedError(f"Method '{func.__name__}' does not override any method from the base class.")
        return func(*args, **kwargs)
    return wrapper


class TaskTemplate:
    def __init__(self, task_name: str):
        self.task_name = task_name

    def run(self, *args, **kwargs):
        raise NotImplementedError('run() method not implemented in TaskTemplate')
    
    def __call__(self, *args, **kwargs):
        self.run(args, kwargs)


class CMakePreBuildTask(TaskTemplate):
    def __init__(self, cmake_build_dir: str='build'):
        super().__init__('CMakePreBuildTask')
        self.cmake_build_dir = ROOT_PATH / cmake_build_dir

    @override
    def run(self, *args, **kwargs):
        type: str = kwargs.get('type', 'Debug')

        if not os.path.exists(self.cmake_build_dir):
            os.makedirs(self.cmake_build_dir, exist_ok=True)
            logging.info(f"Created CMake build directory '{self.cmake_build_dir}'.")

        CMAKE_COMMAND = ' '.join([
            'cmake',
            '-S', 
            ROOT_PATH.as_posix(),
            '-B',
            self.cmake_build_dir.as_posix(),
            f'-DCMAKE_BUILD_TYPE={type}',
            '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON',
        ])

        logging.info(f"Running CMake command: {CMAKE_COMMAND}")
        os.system(CMAKE_COMMAND)


class GenerateAOpsTask(TaskTemplate):
    def __init__(self):
        super().__init__('GenerateAOpsTask')
        # import .mllm.Schema.aops

    @override
    def run(self, *args, **kwargs):
        pass


def build_pipeline():
    logging.info('Build pipeline started...')
    CMakePreBuildTask()(type='Debug')


if __name__ == '__main__':
    build_pipeline()
